#ifndef _TEXTBUFFER_H_
#define _TEXTBUFFER_H_

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <stack>
#include <atomic>

class EditorCommand;

/**
 * \class TextBuffer
 *
 * \brief
 *
 * This class is a utility class to perform basic text editor functionalities:
 * - Insert
 * - Erase
 * - Replace
 * - Undo
 * - Redo
 */
class TextBuffer
{
public:
	/**
      * \brief default constructor
      */
	TextBuffer() = default;
	/**
      * \brief constructor taking argument of a filename
      * \param fileName file name to read from
      */
	explicit TextBuffer(const std::string& fileName);
	/**
      * \brief default destructor
      */
	~TextBuffer();


	/** \brief insert a substring at a position
      * \param lineNum line number (indexed from 1)
      * \param colNum column number (indexed from 1)
      * \param text substring to insert
      * \return true on success; otherwise false
      */
	bool insert(const size_t lineNum, const size_t colNum, const std::string& text);
	/** \brief append a new line at the end of the file
	  * \param text string to append
	  * \return true on success; otherwise false
      */
	bool append(const std::string& text);


	/** \brief erase N charecters at a given position
      * \param lineNum line number (indexed from 1)
      * \param colNum column number (indexed from 1)
      * \param numOfChar number of charecters to be removed
      * \return true on success; otherwise false
      */
	bool erase(const size_t lineNum, const size_t colNum, const size_t numOfChar);
	/** \brief erase N charecters from the end of the file
	  * \param numOfChar number of charecters to be removed
	  * \return true on success; otherwise false
      */
	bool erase(const size_t numOfChar);

	/** \brief replace a given string with another string
      * \param src source string
      * \param dest destination string
      * \return true on success; otherwise false
      */
	bool replace(const std::string& src, const std::string& dest);

	/** \brief execute undo command
	  * \return true on success; otherwise false
      */
	bool undo();
	/** \brief execute redo command
	  * \return true on success; otherwise false
      */
	bool redo();

	/** \brief load texts from a given file
	  * \param fileName name of the file
	  * \return true on success; otherwise false
      */
	bool loadFromFile(const std::string& fileName);
	/** \brief save texts to a given file
	  * \param fileName name of the file
	  * \return true on success; otherwise false
      */
	bool saveToFile(const std::string& fileName) const;


	/** \brief get current line number
      */
	size_t getCurLineNum() const;
	/** \brief get current column number
      */
	size_t getCurColNum() const;
	/** \brief total number of lines in the file
      */
	size_t numOfLines() const;
	/** \brief total number of characters in the current line
      */
	size_t numOfChars() const;
	/** \brief get texts of a given line (if no argument passed return the current line)
	  * \param lineNum number of the line
	  * \return return string of the given line
      */
	std::string getLine(const size_t lineNum = 0) const;
	/** \brief remove string of the given line (if no argument passed return the current line)
	  * \param lineNum number of the line
	  * \return return true on success; otherwise false
      */
	bool removeLine(const size_t lineNum = 0);
	/** \brief clear everything from the buffer
      */
	void clearAll();

private:
	/*
	 * doubly link list containing list of charcters
	 * each node in the doubly link list representing a signle line
	 */
	std::list<std::vector<char>> m_buffer;
	// current line text
	std::vector<char> curLine;

	// stack of undo commands
	std::stack<EditorCommand*> undoCommands;
	// stack of redo commands
	std::stack<EditorCommand*> redoCommands;

	// current line number
	size_t curLineNum {1};
	// current column number
	size_t curColNum {1};

	// a flag to represent undo/redo command
	std::atomic<bool> isUndoRedo {false};


	/** \brief update current line number
      */
	void setCurLine();
	/** \brief get the texts of a given line number (if no argument passed return the current line)
	  * \param lineNum number of the line
	  * \return array of chars
      */
	std::vector<char>& getLineRef(const size_t lineNum = 0);
	/** \brief clear the redo stack
      */
	void clearRedoCommands();
	/** \brief clear the undo stack
      */
	void clearUndoCommands();
	/** \brief check if the command is comming from undo/redo
	  * \param return true if the command is undo/redo;otherwise false
      */
	bool isUndoRedoCommand() const;
};

#endif