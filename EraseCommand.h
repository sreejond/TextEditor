#ifndef _ERASECOMMAND_H_
#define _ERASECOMMAND_H_

#include <string>

#include "EditorCommand.h"

/**
 * \class EraseCommand
 *
 * \brief
 *
 * This class is reponsible for undo/redo of erase command
 */
class EraseCommand final : public EditorCommand 
{
public:
	/**
      * \brief constructor
      * \param lineNum line number
      * \param colNum column number
      * \param text the erased text
      */
    EraseCommand(const size_t lineNum, const size_t colNum, const std::string text);
    /**
      * \brief default destructor
      */
    ~EraseCommand();

    /**
      * \brief undo the command
      */
    virtual void undo(TextBuffer& buffer) override;
    /**
      * \brief redo the command
      */
    virtual void redo(TextBuffer& buffer) override;

private:
	// line number where the text erased
    const size_t m_lineNum;
    // column number where the text erased
    const size_t m_colNum;
    // number of charecters erased
    const size_t m_numOfChar;
    // erased text
    const std::string m_text;
};

#endif
