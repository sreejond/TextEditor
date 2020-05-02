#ifndef _APPENDCOMMAND_H_
#define _APPENDCOMMAND_H_

#include <string>

#include "EditorCommand.h"

/**
 * \class AppendCommand
 *
 * \brief
 *
 * This class is reponsible for undo/redo of append command
 */
class AppendCommand final : public EditorCommand 
{
public:
	/**
      * \brief constructor
      * \param lineNum line number
      * \param text the appended text
      */
    AppendCommand(const size_t lineNum, const std::string text);
    /**
      * \brief default destructor
      */
    ~AppendCommand();

    /**
      * \brief undo the command
      */
    virtual void undo(TextBuffer& buffer) override;
    /**
      * \brief redo the command
      */
    virtual void redo(TextBuffer& buffer) override;

private:
	// line number where the text appended
    const size_t m_lineNum;
    // appended text
    const std::string m_text;
};

#endif
