#ifndef _EDITORCOMMAND_H_
#define _EDITORCOMMAND_H_

class TextBuffer;

/**
 * \class EditorCommand
 *
 * \brief
 *
 * This class ack as an interface for all the concrete text editor commands like:
 * - Append
 * - Insert
 * - Erase
 * - Replace
 * - Remove
 */
class EditorCommand 
{
public:

	/**
      * \brief default constructor
      */
    EditorCommand() = default;
    /**
      * \brief default destructor
      */
    virtual ~EditorCommand() {}

    /**
      * \brief undo the command
      */
    virtual void undo(TextBuffer& buffer) = 0;
    /**
      * \brief redo the command
      */
    virtual void redo(TextBuffer& buffer) = 0;
};

#endif
