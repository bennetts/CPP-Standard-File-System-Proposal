#include <string>
#include <vector>

// A new file standard for the C++ language.
//replaces EMBED precomiler with a function in the language that accepts STATIC as a type of file to embed at compile time.

struct file {
	unsigned int INTERNAL_ID;
}; //Metadata object for the user to reference their files for heuristics or as an object in the array.

class filehandler_internal {
private:
	std::vector <CPP_INTERNAL_FILE> filedata;

public:
	file fileload(std::string path, bool load_into_memory_on_program_startup); // A method to load a file based on the parameters.

	//General file handling methods.
		int seek(file from, unsigned int position); // A method to seek to a specific position in the file stream.
		char stream(file from); // A method to read the file as a stream of bytes.
		int delete_file_from_program(file to_delete); //Cleans up embedded data and destroys the internal file object.
		int delete_embedded_data(file from_memory); // Free up RAM used by embed.

	//Dynamic file handling methods.
		int close(file file_to_close); // A method to close the file stream if not embedded.
		int embed(file into_memory, unsigned int starting_offset = 0, unsigned int bytes_to_load = 0); // "0 bytes to load" means load the entire rest of the file.
		int load_percentage_complete(file file_to_check);

	//Copy handling
		// A method to copy the file data. Does not require initial loading. Will automatically open the stream and close it after copying if necessary.
		std::vector<char> copy(file from, unsigned int starting_offset = 0, unsigned int bytes_to_copy = 0);
		// A method to expose the internal vector of bytes that holds the file data if it was loaded statically. This allows for direct manipulation of the file data in memory without copying it.
		std::vector<char>* expose(file from_memory); 
} filehandler; //let's make sure it's a singleton guarantee

//This requires compiler and linker changes for static loading of files.
