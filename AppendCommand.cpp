#include "AppendCommand.h"
#include "TextBuffer.h"

AppendCommand::AppendCommand(const size_t lineNum, const std::string text)
: m_lineNum (lineNum)
, m_text (std::move(text))
{}

AppendCommand::~AppendCommand()
{}

void AppendCommand::undo(TextBuffer& buffer)
{
	buffer.removeLine(m_lineNum);
}

void AppendCommand::redo(TextBuffer& buffer)
{
	buffer.append(m_text);
}