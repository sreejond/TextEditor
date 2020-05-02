#include "EraseCommand.h"
#include "TextBuffer.h"

EraseCommand::EraseCommand(const size_t lineNum, const size_t colNum, const std::string text)
: m_lineNum (lineNum)
, m_colNum (colNum)
, m_numOfChar (text.size())
, m_text (std::move(text))

{}

EraseCommand::~EraseCommand()
{}

void EraseCommand::undo(TextBuffer& buffer)
{
	buffer.insert(m_lineNum, m_colNum, m_text);
}

void EraseCommand::redo(TextBuffer& buffer)
{
	buffer.erase(m_lineNum, m_colNum, m_numOfChar);
}