#ifndef _REPLACECOMMAND_H_
#define _REPLACECOMMAND_H_

#include <string>
#include <vector>

#include "EditorCommand.h"

/**
 * \class ReplaceCommand
 *
 * \brief
 *
 * This class is reponsible for undo/redo of replace command
 */
class ReplaceCommand final : public EditorCommand 
{
public:
	/**
      * \brief constructor
      * \param src source text
      * \param dest destination text
      * \param positions a list of pairs(line number, column number) where replace operatoin occured
      */
    ReplaceCommand(const std::string src, const std::string dest, const std::vector<std::pair<size_t, size_t>> positions);
    /**
      * \brief default destructor
      */
    ~ReplaceCommand();

    /**
      * \brief undo the command
      */
    virtual void undo(TextBuffer& buffer) override;
    /**
      * \brief redo the command
      */
    virtual void redo(TextBuffer& buffer) override;

private:
	// source text
    const std::string m_src;
    // destination text
    const std::string m_dest;
    // a list of pairs(line number, column number) where replace operatoin occured
    const std::vector<std::pair<size_t, size_t>> m_positions;
};

#endif
