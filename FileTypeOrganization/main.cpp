//by. Sean Jesky i hope this helps someone out there. Please use in a responsible way.. 
/* 
 * FILE('s): main.cpp
 * DATE&TIME: feb 15th 2023
 * CREATED_BY: Sean Jesky ()
 * CREATED_FOR: the dream
 * WHAT_IT_DOES:  This data is saved in users requested location. Segregation and organization of file extension type. 
              
 */

#include <filesystem>
namespace fs = std::filesystem;
#include <exception>
#include <vector>
using std::vector;
#include <iostream>
#include <string>
using std::string;
#include <algorithm>
#include  <fstream>
using std::ofstream;
/// <summary>
/// get data from the selected directory
/// </summary>
/// <param name="directory"></param>
/// <returns>vector</returns>
const inline vector<fs::path> collect_relivant_files(const fs::path& directory)
{

	//save file names to files;
	vector<fs::path> files;
	std::vector<fs::path>* p_files = &files;
	files.reserve(5000000);
	try {
		for (const fs::directory_entry& directory : fs::recursive_directory_iterator{ directory })
		{
			if (!fs::is_empty(directory)) {
				const fs::path& file_path = directory;
				const fs::path* file_path_p = &file_path;

				if (!fs::is_directory(*file_path_p) && fs::file_size(file_path) > 0)
				{
					if (file_path_p->has_extension())
					{
						p_files->push_back(*file_path_p);
					}
				}
			}
		}
	}
	catch (std::filesystem::filesystem_error& err) {
		std::cout << "Filesys error" << "\n" << err.what() << std::endl;
	}

	std::sort(p_files->begin(), p_files->end());

	return files;
}
/// <summary>
/// 
/// </summary>
/// <param name="collected_data"></param>
/// <returns></returns>
//get extensions based on file extensions within lookup directory
//and push back one of each to vector to exclude duplicates:
const inline vector<fs::path> get_extensions(vector<fs::path>* collected_data)
{
	vector<string> extension_types;
	vector<string>* p_types = &extension_types;
	//to increasse the speed of the code, reserve the amount of space that will be needed by the code
	extension_types.reserve(collected_data->size());
	//go through the collected data(every file and directory)
	for (const auto& current_filename : (*(collected_data)))
	{
		//if the file has a extension, this is the data we need, continue
		if (current_filename.has_extension())
		{
			//save the extensions of all the files [this can be combined with the steps below, or moved into its own function]
			std::string path_str = current_filename.extension().string();
			p_types->push_back(path_str);
		}
	}
	//create a vector to save the valid file extension data within
	vector<fs::path> types_no_duplicates;
	vector<fs::path>* p_types_no_duplicates = &types_no_duplicates;
	//sort the data by alpha. order.
	std::sort(p_types->begin(), p_types->end());
	//go through the sorted vector one by one:
	for (int i = 0; i != p_types->size(); ++i)
	{
		//if the value from the vector doesn't repeat itself..  fix ERROR
		if ((*(p_types))[i] != (*(p_types))[i - 1])
		{
			//then place it in the new vector, this is the list that will create the dir.list to copy to
			p_types_no_duplicates->push_back((*(p_types))[i]);
			//print the extensions that will become the directories to copy to
			std::cout << (*(p_types))[i] << '\n';
		}
	}
	//send the valid file extension type data to vector for creating the directories
	return types_no_duplicates;
}

inline void create_directory_from_extension_type(const fs::path& base_save_location, const vector<fs::path>& extensions)
{
	//vector<fs::path> save_location;
	for (auto& i : extensions)	//go through extension types presented from prev. function.
	{
		fs::create_directory(base_save_location.string() + i.string());		//create dir based on extensions
	}
}
void copy_relevent_files(const fs::path dest, vector<fs::path>* files_to_copy, vector<fs::path>* extensions)
{
	//call function to create the directorys needed to copy to
	create_directory_from_extension_type(dest, *extensions);
	for (const auto& ext : *extensions)
	{
		int i = 0;
		int* p_i = &i;
		for (const auto& files : (*(files_to_copy)))
		{
			if (files.has_extension())
			{
				if (files.extension() == ext)
				{
					try
					{
						//copy files to new location that are based on its extension
						fs::copy(files, dest.string() + ext.string(), fs::copy_options::recursive);
						//create the filename destination and save location to be used by the functions below:
						const fs::path core_path = dest.string() + ext.string();
						const fs::path save_this = core_path.string() + "\\" + files.filename().string();
						const fs::path save_at = core_path.string() + "\\" + files.filename().string() + "_" + std::to_string(++(*(p_i))) + "_" + std::to_string(time(NULL)) + files.extension().string();
						//rename all the files in their new location....after they have been copied, this should be rewritten with Multi-threads.
						if (fs::exists(save_this))
						{
							fs::rename(save_this, save_at);
						}
					}
					//if an error occurs, print error in log file for later lookup if needed by user.
					catch (std::runtime_error& err)
					{
						ofstream logs_(dest.string() + "error.txt", std::ios::app);
						logs_ << err.what() << "\n" << dest.string() + ext.string() << '\n';

					}
				}
			}    //comp = false;
		}
	}
}

int main(int argv, char* argc[])
{
	//onlu using pointers when able for one simple reasion:
	//im doing IO, so every bit, every second is relivant in this case.. which;
	//i didnt add them until after i examined the output performance

	std::string copy_from = argc[1];
	const fs::path path_to_copy_from = copy_from;

	//const fs::path path_to_copy_from = "";
	vector<fs::path> files;
	vector<fs::path>* p_files = &files;
	files = collect_relivant_files(path_to_copy_from);

	vector<fs::path> extn;
	vector<fs::path>* p_extn = &extn;
	extn = get_extensions(p_files);

	std::string save_location = argc[2];
	const fs::path base_save_location = save_location;

	std::cout << "\n\nThere are:\t" << files.size() << " Files To Be Copied...\n";
	std::cout << "\n\nThere are:\t" << extn.size() << " Extensions Directories To Be Created...\n";

	if (files.size() >= 1000) {
		std::cout << "\n\nPlease Be Patient, There Are >= 1000 Files, Else, Press Ctrl + C To Quit Program.\n";
	}
	copy_relevent_files(base_save_location, p_files, p_extn);
	
}
