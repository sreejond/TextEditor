#ifndef _INSERTCOMMAND_H_
#define _INSERTCOMMAND_H_

#include <string>

#include "EditorCommand.h"

/**
 * \class InsertCommand
 *
 * \brief
 *
 * This class is reponsible for undo/redo of insert command
 */
class InsertCommand final : public EditorCommand 
{
public:
	/**
      * \brief constructor
      * \param lineNum line number
      * \param colNum column number
      * \param text the inserted text
      */
    InsertCommand(const size_t lineNum, const size_t colNum, const std::string text);
    /**
      * \brief default destructor
      */
    ~InsertCommand();

    /**
      * \brief undo the command
      */
    virtual void undo(TextBuffer& buffer) override;
    /**
      * \brief redo the command
      */
    virtual void redo(TextBuffer& buffer) override;

private:
	// line number where the text inserted
    const size_t m_lineNum;
    // column number where the text erased
    const size_t m_colNum;
    // number of charecters inserted
    const size_t m_numOfChar;
    // inserted text
    const std::string m_text;
};

#endif
