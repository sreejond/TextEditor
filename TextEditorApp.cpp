#include <iostream>

#include "TextBuffer.h"


void appendTest()
{
	std::cout << std::endl << "executing appendTest!!" << std::endl;
	
	TextBuffer buffer;
	std::vector<std::string> lines {"add dipanjan", 
									"add das", 
									"add roy", 
									"add dipanjan das roy"};
	for (auto& line : lines)
		buffer.append(line);
	
	for (size_t i = 0; i < buffer.numOfLines(); i++)
	{
		std::string lineFromEditor = buffer.getLine(i + 1);
		if (lineFromEditor != lines[i])
		{
			std::cout << "appendTest failed!!" << std::endl;
			return;
		}
	}

	std::cout << "appendTest passed!!" << std::endl;
}

void removeLineTest()
{
	std::cout << std::endl << "executing removeLineTest!!" << std::endl;
	
	TextBuffer buffer;
	std::vector<std::string> lines {"add everything", 
									"add dipanjan", 
									"add das", 
									"add roy", 
									"add dipanjan das roy"};
	for (auto& line : lines)
		buffer.append(line);
	
	buffer.removeLine(4);
	buffer.removeLine(4);
	for (size_t i = 0; i < buffer.numOfLines(); i++)
	{
		std::string lineFromEditor = buffer.getLine(i + 1);
		if (lineFromEditor != lines[i])
		{
			std::cout << "removeLineTest failed!!" << std::endl;
			return;
		}
	}

	std::cout << "removeLineTest passed!!" << std::endl;	
}

void insertTest()
{
	std::cout << std::endl << "executing insertTest!!" << std::endl;
	
	TextBuffer buffer;
	std::vector<std::string> lines {"add everything", 
									"add dipanjan", 
									"add das", 
									"add roy", 
									"add dipanjan das roy"};
	for (auto& line : lines)
		buffer.append(line);
	
	buffer.insert(1, 1, "yes ");
	buffer.insert(4, 8, " gentleman");

	lines[0] = "yes add everything";
	lines[3] = "add roy gentleman";

	for (size_t i = 0; i < buffer.numOfLines(); i++)
	{
		std::string lineFromEditor = buffer.getLine(i + 1);
		if (lineFromEditor != lines[i])
		{
			std::cout << "insertTest failed!!" << std::endl;
			return;
		}
	}

	std::cout << "insertTest passed!!" << std::endl;		
}

void eraseTest()
{
	std::cout << std::endl << "executing eraseTest!!" << std::endl;
	
	TextBuffer buffer;
	std::vector<std::string> lines {"add everything", 
									"add dipanjan", 
									"add das", 
									"add roy", 
									"add dipanjan das roy"};
	for (auto& line : lines)
		buffer.append(line);
	
	buffer.erase(1, 4, 11);
	buffer.erase(5, 1, 4);

	lines[0] = "add";
	lines[4] = "dipanjan das roy";

	for (size_t i = 0; i < buffer.numOfLines(); i++)
	{
		std::string lineFromEditor = buffer.getLine(i + 1);
		if (lineFromEditor != lines[i])
		{
			std::cout << "eraseTest failed!!" << std::endl;
			return;
		}
	}

	std::cout << "eraseTest passed!!" << std::endl;		
}

void replaceTest()
{
	std::cout << std::endl << "executing replaceTest!!" << std::endl;
	
	TextBuffer buffer;
	std::vector<std::string> lines {"add everything", 
									"add dipanjan", 
									"add das", 
									"add roy", 
									"add dipanjan das roy"};
	for (auto& line : lines)
		buffer.append(line);
	
	buffer.replace("add", "+");

	lines[0] = "+ everything"; 
	lines[1] = "+ dipanjan";
	lines[2] = "+ das";
	lines[3] = "+ roy"; 
	lines[4] = "+ dipanjan das roy";

	for (size_t i = 0; i < buffer.numOfLines(); i++)
	{
		std::string lineFromEditor = buffer.getLine(i + 1);
		if (lineFromEditor != lines[i])
		{
			std::cout << "replaceTest failed!!" << std::endl;
			return;
		}
	}

	std::cout << "replaceTest passed!!" << std::endl;			
}

void undoTest()
{
	std::cout << std::endl << "executing undoTest!!" << std::endl;
	
	TextBuffer buffer;
	std::vector<std::string> lines {"add everything", 
									"add dipanjan", 
									"add das", 
									"add roy", 
									"add dipanjan das roy"};
	for (auto& line : lines)
		buffer.append(line);
	
	buffer.insert(1, 1, "yes ");
	buffer.erase(5, 14, 4);
	buffer.replace("add", "+");
	buffer.undo();
	buffer.undo();
	buffer.undo();

	for (size_t i = 0; i < buffer.numOfLines(); i++)
	{
		std::string lineFromEditor = buffer.getLine(i + 1);
		if (lineFromEditor != lines[i])
		{
			std::cout << "undoTest failed!!" << std::endl;
			return;
		}
	}

	std::cout << "undoTest passed!!" << std::endl;				
}

void redoTest()
{
	std::cout << std::endl << "executing redoTest!!" << std::endl;
	
	TextBuffer buffer;
	std::vector<std::string> lines {"add everything", 
									"add dipanjan", 
									"add das", 
									"add roy", 
									"add dipanjan das roy"};
	for (auto& line : lines)
		buffer.append(line);
	
	buffer.insert(1, 1, "yes ");
	buffer.erase(5, 14, 4);
	buffer.replace("add", "+");
	buffer.undo();
	buffer.undo();
	buffer.undo();
	buffer.redo();
	buffer.redo();
	buffer.redo();

	lines[0] = "yes + everything"; 
	lines[1] = "+ dipanjan";
	lines[2] = "+ das";
	lines[3] = "+ roy"; 
	lines[4] = "+ dipanjan roy";

	for (size_t i = 0; i < buffer.numOfLines(); i++)
	{
		std::string lineFromEditor = buffer.getLine(i + 1);
		if (lineFromEditor != lines[i])
		{
			std::cout << "redoTest failed!!" << std::endl;
			return;
		}
	}

	std::cout << "redoTest passed!!" << std::endl;				
}

int main()
{
	appendTest();
	removeLineTest();
	insertTest();
	eraseTest();
	replaceTest();
	undoTest();
	redoTest();
	
	return 0;
}