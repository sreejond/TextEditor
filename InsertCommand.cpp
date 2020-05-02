#include "InsertCommand.h"
#include "TextBuffer.h"

InsertCommand::InsertCommand(const size_t lineNum, const size_t colNum, const std::string text)
: m_lineNum (lineNum)
, m_colNum (colNum)
, m_numOfChar (text.size())
, m_text (std::move(text))
{}

InsertCommand::~InsertCommand()
{}

void InsertCommand::undo(TextBuffer& buffer)
{
	buffer.erase(m_lineNum, m_colNum, m_numOfChar);
}

void InsertCommand::redo(TextBuffer& buffer)
{
	buffer.insert(m_lineNum, m_colNum, m_text);
}