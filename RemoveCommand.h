#ifndef _REMOVECOMMAND_H_
#define _REMOVECOMMAND_H_

#include <string>

#include "EditorCommand.h"

/**
 * \class RemoveCommand
 *
 * \brief
 *
 * This class is reponsible for undo/redo of remove command
 */
class RemoveCommand final : public EditorCommand 
{
public:
	/**
      * \brief constructor
      * \param lineNum line number
      * \param text the removed text
      */
    RemoveCommand(const size_t lineNum, const std::string text);
    /**
      * \brief default destructor
      */
    ~RemoveCommand();

    /**
      * \brief undo the command
      */
    virtual void undo(TextBuffer& buffer) override;
    /**
      * \brief redo the command
      */
    virtual void redo(TextBuffer& buffer) override;

private:
	// line number where the text removed
    const size_t m_lineNum;
    // removed text
    const std::string m_text;
};

#endif
