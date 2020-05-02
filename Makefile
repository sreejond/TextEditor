CC=g++
CFLAGS=-std=c++17 -c -g -Wall

all: TextEditor

TextEditor: TextEditorApp.o TextBuffer.o InsertCommand.o EraseCommand.o ReplaceCommand.o AppendCommand.o RemoveCommand.o
	$(CC) TextEditorApp.o TextBuffer.o InsertCommand.o EraseCommand.o ReplaceCommand.o AppendCommand.o RemoveCommand.o -o TextEditor

TextBuffer.o: TextBuffer.cpp
	$(CC) $(CFLAGS) TextBuffer.cpp

EditorCommand.o: EditorCommand.cpp
	$(CC) $(CFLAGS) EditorCommand.cpp

InsertCommand.o: InsertCommand.cpp
	$(CC) $(CFLAGS) InsertCommand.cpp

EraseCommand.o: EraseCommand.cpp
	$(CC) $(CFLAGS) EraseCommand.cpp

ReplaceCommand.o: ReplaceCommand.cpp
	$(CC) $(CFLAGS) ReplaceCommand.cpp

AppendCommand.o: AppendCommand.cpp
	$(CC) $(CFLAGS) AppendCommand.cpp

RemoveCommand.o: RemoveCommand.cpp
	$(CC) $(CFLAGS) RemoveCommand.cpp

TextEditorApp.o: TextEditorApp.cpp
	$(CC) $(CFLAGS) TextEditorApp.cpp
	
clean:
	rm -rf *.o TextEditor
