#include "RemoveCommand.h"
#include "TextBuffer.h"

RemoveCommand::RemoveCommand(const size_t lineNum, const std::string text)
: m_lineNum (lineNum)
, m_text (std::move(text))
{}

RemoveCommand::~RemoveCommand()
{}

void RemoveCommand::undo(TextBuffer& buffer)
{
	buffer.append(m_text);
}

void RemoveCommand::redo(TextBuffer& buffer)
{
	buffer.removeLine(m_lineNum);
}