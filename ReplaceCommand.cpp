#include "ReplaceCommand.h"
#include "TextBuffer.h"

ReplaceCommand::ReplaceCommand(const std::string src, const std::string dest, const std::vector<std::pair<size_t, size_t>> positions)
: m_src (std::move(src))
, m_dest (std::move(dest))
, m_positions (std::move(positions))
{}

ReplaceCommand::~ReplaceCommand()
{}

void ReplaceCommand::undo(TextBuffer& buffer) 
{
	for (auto it = m_positions.rbegin(); it != m_positions.rend(); it++)
	{
		buffer.erase(it->first, it->second, m_dest.size());
		buffer.insert(it->first, it->second, m_src);
	}
}

void ReplaceCommand::redo(TextBuffer& buffer) 
{
	for (auto& it : m_positions)
	{
		buffer.erase(it.first, it.second, m_src.size());
		buffer.insert(it.first, it.second, m_dest);
	}
}