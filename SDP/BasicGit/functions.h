#pragma once

#include <stdio.h>
#include <fstream>
#include <iomanip>  //setfill() , setw()
#include <stdlib.h> //to_string();
#include <cstdio>   //std::remove();

#include <ctime> //time_t

#include <dirent.h>
#include <sys/stat.h> //S_ISDIR();

#include <string>
#include "prefix_tree.h"

bool init_repository(const std::string &path); //path to the directory that will be initialized as a repository.

void make_commit(const std::string &path,      //path to the repository.
                 const std::string &person,    //name of the person who's commiting.
                 const std::string &message);  //commit message.

void get_files(const std::string &rhs_path, //path to the directory within a repository.
               prefix_tree &tree,           //tree to fill.
               prefix_tree::iterator node); //iterator to the current node.

std::string is_in_repository(const std::string &path); //path to the passed in directory.

int get_commit_id(std::string path);                   //path to the commits directory.

void prev_commit(file_map &original, //hash map which will store the original files paths as Keys and their hashes as Values.
                 file_map &copy,     //hash map which will store the coppied files paths as Keys and their hashes as Values.
                 std::string path,   //path to the commits directory.
                 unsigned int id);   //id of the current commit, which will be decremented by 1.

void commit_file(file_map &original,     //hash map with the original files paths as Keys and their hashes as Values.
                 file_map &copy,         //hash map with the coppied files paths as Keys and their hashes as Values.
                 std::ofstream &info,    //path to info.bin.
                 std::string from,       //path to original file.
                 std::string to,         //path to the commit directory.
                 const file_data &file); //actual file to store.

bool prev_committed(file_map &orignal,        //hash map with the original files paths as Keys and their hashes as Values.
                    const file_data &file,    //file to check for.
                    const std::string &from); //original path of the file.

void commit_dir(std::ofstream &info,        //path to info.bin.
                file_map &original,         //hash map with the original files paths as Keys and their hashes as Values.
                file_map &copy,             //hash map with the coppied files paths as Keys and their hashes as Values.
                prefix_tree::iterator root, //iterator to the root of the tree.
                std::string to);            //path to the comit directory.

void update_log(std::string &log_path,         //path to the log file.
                const std::string &name,       //name of the committer.
                const std::string &msg,        //commit message.
                const unsigned int commit_id); //id of the commit.

//
// Initialized the passed in directory as a repository.
//
bool init_repository(const std::string &path)
{
    puts("Initializing repository...");

    DIR *dp;
    dp = opendir(path.c_str());
    //
    // Checks if the path is valid.
    //
    if (dp)
    {
        //
        //If the path is valid, checks if the directory is already a repository.
        //
        std::string commits(path);
        commits.append("/commits");

        closedir(dp);

        puts("Looking for the commits directory...");
        dp = opendir(commits.c_str());

        //
        // If it's not a repository, create a commits directory.
        //
        if (!dp)
        {
            puts("Making a commits directory...");
            int created = mkdir(commits.c_str(), S_IRWXU); //creates a directory for the commits
                                                           //with read/write/execute permissions for the user.

            if (created == 0)
            {
                puts("Successfully created the commits directory!");

                puts("Making a log file...");
                std::string log_path = commits;
                log_path.append("/log.txt");

                std::ofstream log(log_path.c_str());
                if (log)
                {
                    puts("Successfully created a log file!");
                    log.close();
                }

                // if the program fails to create a log file,
                //we delete the commits directory
                //to be able to attempt re-init the directory.
                else
                {
                    std::remove(commits.c_str());
                    return 0;
                }
                return 1;
            }

            else
                puts("Failed to create the commits directory.");
        }
        else
            puts("Repository already initialized.");

        closedir(dp);
    }
    else
        puts("Invalid path.");
    return 0;
}

void make_commit(const std::string &path,
                 const std::string &person,
                 const std::string &message)
{

    std::string commits_path = is_in_repository(path);

    puts("Prepping file(s) for commit...");

    unsigned int commit_id = get_commit_id(commits_path);

    std::string id = std::to_string(commit_id);
    std::string curr_commit_path = commits_path;
    curr_commit_path.append("/");
    curr_commit_path.append(id);

    int created = mkdir(curr_commit_path.c_str(), S_IRWXU);
    if (created != 0)
        throw "Commit aborted. Failed to create a directory for the current commit.\n";

    std::string info_path = curr_commit_path;
    info_path.append("/info.bin");

    std::ofstream info(info_path.c_str(), std::ios::binary);

    if (info)
    {
        file_map original_data; //hash map with the original files paths as Keys and their hashes as Values.
        file_map copy_data;     //hash map with the coppied files paths as Keys and their hashes as Values.
                                //NOTE: Both hashes are the same.
        if (commit_id > 1)
        {
            prev_commit(original_data,
                        copy_data,
                        commits_path,
                        commit_id);
        }

        struct stat sb;
        stat(path.c_str(), &sb);
        //
        //Check whether the passed in argument is a file or a directory.
        //
        if (S_ISDIR(sb.st_mode))
        {
            //in case it's a directory,
            //builds a prefix tree with all the files in the passed in dir.
            prefix_tree tree(path);
            get_files(path, tree, tree.get_root());
            //tree.print();

            commit_dir(info,
                       original_data,
                       copy_data,
                       tree.get_root(),
                       curr_commit_path);
        }
        else
        {
            //in case it's a single file,
            //we create a single file_data variable.
            file_data file(path);
            commit_file(original_data,
                        copy_data,
                        info,
                        path,
                        curr_commit_path,
                        file);
        }
        info.close();
    }
    else
        throw "Failed to create an info.bin file.\n";

    update_log(commits_path, person, message, commit_id);

    printf("Files commited under id: %u\n", commit_id);
}

//
// Checks whether the passed in path is part of a repository
//by searching inside out for the commits directory
//returning the path to the commits directory if it finds it.
//
std::string is_in_repository(const std::string &path)
{
    std::string temp(path);
    std::string commits_path(path);
    commits_path.append("/commits");

    DIR *dp;
    struct dirent ep;

    while (temp != "")
    {
        dp = opendir(commits_path.c_str());
        if (!dp)
        {
            try
            {

                while (*(temp.end() - 1) != '/')
                    temp.erase(temp.length() - 1);

                temp.erase(temp.length() - 1);
            }
            catch (std::out_of_range)
            {
                break;
            }

            commits_path = temp;
            commits_path.append("/commits");
        }
        else
        {
            closedir(dp);
            return commits_path;
        }
    }
    throw "Not a valid repository.\n";
}

//
//Reads the info.bin file inside the previous commit directory,
//and pushes the data into two seperate hash maps.
//the first holds the path to the original files + their hashes,
//while the second holds the path to the file coppies,
//which are stored in the previous commit directory and their hashes(which consequently are the same).
//
void prev_commit(file_map &original,
                 file_map &copy,
                 std::string path,
                 unsigned int id)
{
    --id;
    std::string prev_id = std::to_string(id);
    path.append("/");
    path.append(prev_id);
    path.append("/info.bin");

    std::ifstream info(path.c_str(), std::ios::binary);

    file_data original_file;
    file_data copy_file;

    char original_path[PATH_LENGTH] = {};
    char copy_path[PATH_LENGTH] = {};

    char temp_hash[HASH_LENGTH] = {};

    if (info)
    {
        while (info.read(original_path, PATH_LENGTH))
        {
            info.read(copy_path, PATH_LENGTH);
            info.read(temp_hash, HASH_LENGTH);
            puts(temp_hash);

            original_file.set_name(original_path);
            original_file.set_hash(temp_hash);

            copy_file.set_name(copy_path);
            copy_file.set_hash(temp_hash);

            original.push_back(original_file);
            copy.push_back(copy_file);
        }
        info.close();
    }
    /* 
    file_map::iterator it = map.begin();
    for (; it != map.end(); ++it)
    {
        puts((*it).get_name());
        puts((*it).get_hash());
    } */
}

//
// Gets all the files from the passed in path
//and stores them into a prefix tree.
//
void get_files(const std::string &rhs_path,
               prefix_tree &tree,
               prefix_tree::iterator node)
{
    DIR *dp;
    struct dirent *ep;

    prefix_tree::iterator node_c = node;
    dp = opendir(rhs_path.c_str());

    if (dp)
    {
        while ((ep = readdir(dp)))
        {
            if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0 && strcmp(ep->d_name, "commits") != 0)
            {
                std::string name(ep->d_name);
                std::string path(rhs_path);
                path.append("/");
                path.append(name);

                if (ep->d_type == DT_DIR)
                {
                    name.append("/");
                    node_c = tree.push_folder(node, name);
                    get_files(path, tree, node_c);
                }
                else
                {
                    tree.push_file(node, path);
                }
            }
        }
    }
    else
        throw "Failed to open the directory.\n";

    closedir(dp);
}

//
// Commits a single file by given path.
//
void commit_file(file_map &original,
                 file_map &copy,
                 std::ofstream &info,
                 std::string from,
                 std::string to,
                 const file_data &file)
{

    char temp_path[PATH_LENGTH] = {};
    strcpy(temp_path, from.c_str());

    info.write(temp_path, PATH_LENGTH);

    to.append("/");
    to.append(file.get_name());

    if (!prev_committed(original, file, from))
    {
        info.write(temp_path, PATH_LENGTH);

        std::ifstream source(from.c_str(), std::ios::binary);
        std::ofstream dest(to.c_str(), std::ios::binary);
        dest << source.rdbuf();

        dest.close();
        source.close();
    }
    else
    {
        strcpy(temp_path, to.c_str());
        info.write(temp_path, PATH_LENGTH);
    }
    info.write(file.get_hash(), HASH_LENGTH);
}

//
//Commits a whole directory.
//
void commit_dir(std::ofstream &info,
                file_map &original,
                file_map &copy,
                prefix_tree::iterator root,
                std::string to)
{
    static std::string dir;
    std::string temp;

    dir.append(root->directory.c_str());
    file_map::iterator file_it = root->files.begin();
    if (file_it)
    {
        //puts((*file_it).get_name());
        temp = dir;
        for (; file_it != root->files.end(); ++file_it)
        {
            temp.append("/");
            temp.append((*file_it).get_name());
            commit_file(original,
                        copy,
                        info,
                        temp,
                        to,
                        (*file_it));
            temp = dir;
        }
    }

    auto folder_it = root->folders.begin();
    for (; folder_it != root->folders.end(); ++folder_it)
    {
        dir.append("/");
        commit_dir(info,
                   original,
                   copy,
                   *(*(folder_it)),
                   to);
    }
}

//
// Get's the id of the last commit for the log.txt file
//and return the id of the next commit.
//
int get_commit_id(std::string path)
{
    unsigned int id = 0, temp = 0;
    DIR *dp;
    struct dirent *ep;

    dp = opendir(path.c_str());

    if (dp)
    {
        while ((ep = readdir(dp)))
        {
            if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0)
            {
                temp = atoi(ep->d_name);
                if (id < temp)
                    id = temp;
            }
        }
        closedir(dp);
    }
    return id + 1;
}

//
//  updates the log file in the commits directory.
//
void update_log(std::string &log_path,
                const std::string &name,
                const std::string &msg,
                const unsigned int commit_id)
{
    log_path.append("/log.txt");
    std::ofstream log(log_path.c_str(), std::ios::app);

    time_t t = time(0);
    struct tm *now = localtime(&t);

    if (log)
    {
        log << commit_id
            << ":"
            << " \"" << msg << "\""
            << " from "
            << std::setfill('0') << std::setw(2)
            << now->tm_hour << ":"
            << std::setfill('0') << std::setw(2)
            << now->tm_min << " "
            << std::setfill('0') << std::setw(2)
            << now->tm_mday << "."
            << std::setfill('0') << std::setw(2)
            << (now->tm_mon + 1) << "."
            << (now->tm_year + 1900) << " by "
            << name
            << '\n';
        log.close();
    }
    else
        throw "Failed to update the log.\n";
}

//
//Checks whether the file was previously committed.
//
bool prev_committed(file_map &original,
                    const file_data &file,
                    const std::string &from)
{
    if (original.get_size())
    {
        const char *hash = original[from];

        if (hash)
        {
            if (strcmp(hash, file.get_hash()) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}