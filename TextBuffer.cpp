#include <cassert>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "TextBuffer.h"
#include "InsertCommand.h"
#include "AppendCommand.h"
#include "RemoveCommand.h"
#include "EraseCommand.h"
#include "ReplaceCommand.h"

TextBuffer::TextBuffer(const std::string& fileName)
{
	loadFromFile(fileName);
}

TextBuffer::~TextBuffer()
{
	clearAll();
}

void TextBuffer::clearAll()
{
	clearUndoCommands();
	clearRedoCommands();
	m_buffer.clear();
	curLineNum = 1;
	curColNum = 1;
}

size_t TextBuffer::numOfLines() const
{
	return m_buffer.size();
}

size_t TextBuffer::numOfChars() const
{
	return curLine.size();
}

size_t TextBuffer::getCurLineNum() const
{
	return curLineNum;
}

size_t TextBuffer::getCurColNum() const
{
	return curColNum;
}

void TextBuffer::setCurLine()
{
	auto it = m_buffer.begin();
	std::advance(it, curLineNum - 1);
	curLine = *it;
}

std::string TextBuffer::getLine(const size_t lineNum /*= 0*/) const
{
	assert(lineNum <= numOfLines()); // TODO: ERROR MSG
	const size_t validLineNum = (lineNum == 0) ? curLineNum : lineNum;
	
	auto it = m_buffer.begin();
	std::advance(it, validLineNum - 1);
	return std::string(it->begin(), it->end());
}

std::vector<char>& TextBuffer::getLineRef(const size_t lineNum /*= 0*/)
{
	assert(lineNum <= numOfLines()); // TODO: ERROR MSG
	const size_t validLineNum = (lineNum == 0) ? curLineNum : lineNum;
	
	auto it = m_buffer.begin();
	std::advance(it, validLineNum - 1);
	return *it;
}

bool TextBuffer::removeLine(const size_t lineNum /*= 0*/)
{
	if (lineNum > numOfLines())	return false;

	const size_t validLineNum = (lineNum == 0) ? curLineNum : lineNum;
	auto it = m_buffer.begin();
	std::advance(it, validLineNum - 1);
	std::string removedText = std::string(it->begin(), it->end());
	m_buffer.erase(it);
	if (validLineNum > numOfLines())
		curLineNum = numOfLines();
	curLineNum = (curLineNum == 0) ? 1 : curLineNum;
	curColNum = 1;
	
	if (!isUndoRedoCommand())
	{
		undoCommands.push(new RemoveCommand(validLineNum, std::move(removedText)));
		clearRedoCommands();
	}
	
	return true;
}

bool TextBuffer::insert(const size_t lineNum, const size_t colNum, const std::string& text)
{
	if (lineNum <= 0 || lineNum > numOfLines())	return false;
	std::vector<char>& line = getLineRef(lineNum);
	if (colNum <= 0 || colNum > line.size() + 1)	return false;

	curLineNum = lineNum;
	curColNum = colNum + text.size();
	
	line.insert(line.begin() + colNum - 1, text.begin(), text.end());

	setCurLine();

	if (!isUndoRedoCommand())
	{
		undoCommands.push(new InsertCommand(lineNum, colNum, std::string(text)));
		clearRedoCommands();
	}

	return true;
}

bool TextBuffer::append(const std::string& text)
{	
	if (numOfLines() != 0)	curLineNum++;
	curColNum = text.size() + 1;

	m_buffer.emplace_back(text.begin(), text.end());

	setCurLine();
	
	if (!isUndoRedoCommand())
	{
		undoCommands.push(new AppendCommand(curLineNum, std::string(text)));
		clearRedoCommands();		
	}
	
	return true;
}

bool TextBuffer::erase(const size_t lineNum, const size_t colNum, const size_t numOfChar)
{
	if (numOfChar == 0 || lineNum <= 0 || lineNum > numOfLines())	return false;
	std::vector<char>& line = getLineRef(lineNum);
	if (colNum <= 0 || colNum > line.size())	return false;

	size_t numOfCharToTheEnd = line.size() - colNum + 1;
	size_t numOfCharToRemove = std::min(numOfChar, numOfCharToTheEnd);

	curLineNum = lineNum;
	curColNum = colNum;

	std::string erasedText(line.begin() + colNum - 1, line.begin() + colNum - 1 + numOfCharToRemove);
	line.erase(line.begin() + colNum - 1, line.begin() + colNum - 1 + numOfCharToRemove);

	setCurLine();
	
	if (!isUndoRedoCommand())
	{
		undoCommands.push(new EraseCommand(lineNum, colNum, std::move(erasedText)));
		clearRedoCommands();
	}

	return true;
}

bool TextBuffer::erase(const size_t numOfChar)
{
	if (numOfChar == 0)	return false;
	
	size_t remainingNumOfChar = numOfChar;
	while (numOfLines() != 0)
	{
		size_t lineIndex = numOfLines();
		std::vector<char>& line = getLineRef(lineIndex);
		if (line.size() == remainingNumOfChar)
		{
			removeLine(lineIndex);
			break;
		}
		else if (line.size() > remainingNumOfChar)
		{
			int diff = line.size() - remainingNumOfChar;
			erase(lineIndex, diff + 1, remainingNumOfChar);
			break;
		}
		else
		{
			remainingNumOfChar -= line.size();
			removeLine(lineIndex);
		}
	}
	return true;
}

bool TextBuffer::replace(const std::string& src, const std::string& dest)
{
	if (src.empty() || src == dest)	return false;
	
	std::vector<std::pair<size_t, size_t>> substrPositions;
	size_t linenum = 1;
	for (auto& line : m_buffer)
	{
		auto it = std::search(line.begin(), line.end(), src.begin(), src.end());
		while (it != line.end())
		{
			size_t colnum = std::distance(line.begin(), it) + 1;
			substrPositions.emplace_back(linenum, colnum);
			line.erase(it, it + src.size());
			line.insert(it, dest.begin(), dest.end());
			it = std::search(line.begin(), line.end(), src.begin(), src.end());
		}
		linenum++;
	}
	curLineNum = 1;
	curColNum = 1;
	
	if (!isUndoRedoCommand())
	{
		undoCommands.push(new ReplaceCommand(std::string(src), std::string(dest), std::move(substrPositions)));
		clearRedoCommands();
	}

	return true;
}

bool TextBuffer::isUndoRedoCommand() const
{
	return isUndoRedo;
}

bool TextBuffer::undo()
{
	if (undoCommands.empty())	return false;
	isUndoRedo = true;
	
	EditorCommand* cmd = undoCommands.top(); undoCommands.pop();
	cmd->undo(*this);
	redoCommands.push(cmd);
	
	isUndoRedo = false;
	return true;
}

bool TextBuffer::redo()
{
	if (redoCommands.empty())	return false;
	isUndoRedo = true;

	EditorCommand* cmd = redoCommands.top(); redoCommands.pop();
	cmd->redo(*this);
	undoCommands.push(cmd);
	
	isUndoRedo = false;
	return true;
}

void TextBuffer::clearUndoCommands()
{
	while (!undoCommands.empty())
	{
		EditorCommand* cmd = undoCommands.top(); undoCommands.pop();
		delete cmd;
	}
}

void TextBuffer::clearRedoCommands()
{
	while (!redoCommands.empty())
	{
		EditorCommand* cmd = redoCommands.top(); redoCommands.pop();
		delete cmd;
	}
}

bool TextBuffer::loadFromFile(const std::string& fileName)
{
	std::ifstream infile(fileName);
	
	if (infile.is_open())
	{
		std::string line;
		while (std::getline(infile, line))
		{
			append(line);
		}
	}
	else return false;

	curLineNum = numOfLines();
	curColNum = numOfChars() + 1;
	return true;
}

bool TextBuffer::saveToFile(const std::string& fileName) const
{
	std::ofstream outfile(fileName);

	if (outfile.is_open())
	{
		for (auto& line : m_buffer)
		{
			outfile << std::string(line.begin(), line.end()) << std::endl;
		}
	}
	else return false;

	return true;
}