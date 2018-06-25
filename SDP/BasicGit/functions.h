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

void make_commit(const std::string &path,     //path to the repository.
                 const std::string &person,   //name of the person who's commiting.
                 const std::string &message); //commit message.

void print_log(const std::string &path); //path to a repository.

void status(const std::string &path); //path to the directory which is supposedly a repository.

void revert(const std::string &repo_path, //path to the supposed repository.
            const char *commit_id,        //id of the commit we need to fetch the file from.
            const char *file_path);       //contains the name of the file.

void get_files(const std::string &rhs_path, //path to the directory within a repository.
               prefix_tree &tree,           //tree to fill.
               prefix_tree::iterator node); //iterator to the current node.

std::string path_to_commits(const std::string &path); //path to the passed in directory.

int get_commit_id(std::string path); //path to the commits directory.

void commit_info(file_map &original, //hash map which will store the original files paths as Keys and their hashes as Values.
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
                std::string full_path,      //holds the path from the root.
                std::string to);            //path to the comit directory.

void update_log(std::string &log_path,         //path to the log file.
                const std::string &name,       //name of the committer.
                const std::string &msg,        //commit message.
                const unsigned int commit_id); //id of the commit.

std::vector<const char *> get_uncommited_files(file_map &last_commit,      //hash map with the original files paths as Keys and their hashes as Values from the last commit.
                                               prefix_tree::iterator root, //iterator pointing to the we're currently in in the prefix_tree.
                                               std::string full_path);     //path appended from the root of the prefix_tree.

const char *fetch_file_hash(file_map &original,            //hash map holding the path to the original files as Keys and their hashes as Values.
                            const std::string &repo_path,  //path to the suposed repository.
                            const std::string &file_name); //name of the file we're looking for.

bool substr_in_path(const char *path,              //path to check.
                    const std::string &repo_path,  //prefix we're looking for.
                    const std::string &file_name); //suffix we're looking for.

void get_version(const std::string path,      //path to the commits dir.
                 unsigned int &curr_version,  //uint to store the curr version in.
                 unsigned int &last_version); //uint to store the last version in.

void update_version(const std::string &path,           //path to the commit dir.
                    const unsigned int &curr_version,  //uint holding the curr version of the repo.
                    const unsigned int &last_version); //uint holding the last version of the repo.

void copy_commit_files(file_map &original_map,     //hash map holding the path to the original files as keys and their hashes as values.
                       file_map &copy_map,         //hash map holding the path to the copy files as keys and their hashes as values.
                       prefix_tree::iterator root, //iterator to the current node we've reached in the prefix tree.
                       std::string path);          //string holding the path from the root node to the current node we've reached.

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

                puts("Making a version file...");
                std::string version_path = commits;
                version_path.append("/version.bin");
                std::ofstream version(version_path.c_str());
                if (version)
                {
                    const unsigned int initial_version = 0;
                    version.write(reinterpret_cast<const char *>(&initial_version), sizeof(unsigned int)); //sets the current version of the repository to 0.
                    version.write(reinterpret_cast<const char *>(&initial_version), sizeof(unsigned int)); //sets the total version of the repositories to 0.

                    puts("Successfully created a version file!");
                    version.close();
                }
                else
                {
                    puts("Failed to create a version file.");
                    std::remove(commits.c_str());
                    return 0;
                }

                puts("Making a log file...");
                std::string log_path = commits;
                log_path.append("/log.txt");

                std::ofstream log(log_path.c_str());
                if (log)
                {
                    puts("Successfully created a log file!");
                    log.close();
                }
                else
                {
                    puts("Failed to create a log file.");
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
    unsigned int curr_version = 0, last_version = 0;

    get_version(path, curr_version, last_version);

    if (curr_version != last_version)
        throw "Cannot commit until you checkout to your latest commit.\n";

    std::string commits_path = path_to_commits(path);

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
            commit_info(original_data,
                        copy_data,
                        commits_path,
                        commit_id - 1);
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

            std::string full_path;

            commit_dir(info,
                       original_data,
                       copy_data,
                       tree.get_root(),
                       full_path,
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
    update_version(commits_path, commit_id, commit_id);

    printf("Files commited under id: %u\n", commit_id);
}

//
// Reads the log.txt file in the commits folder
//of the given repository and outputs it on the console.
//
void print_log(const std::string &path)
{
    std::string log_path = path_to_commits(path);
    log_path.append("/log.txt");

    std::ifstream log(log_path.c_str());

    std::string line;

    if (log)
    {
        puts("Commits:");

        while (std::getline(log, line))
            puts(line.c_str());
    }
}

//
// Prints out the files that were not included in the last commit.
//
void status(const std::string &path)
{
    std::string commits = path_to_commits(path);

    unsigned int curr_commit_id = get_commit_id(commits);

    if (curr_commit_id == 0)
        throw "No commits have been made yet.";

    file_map original_data;
    file_map dummy;

    commit_info(original_data,
                dummy,
                commits,
                curr_commit_id - 1);

    prefix_tree tree(path);
    get_files(path, tree, tree.get_root());

    std::string full_path;
    std::vector<const char *> uf = get_uncommited_files(original_data, //uncommited files.
                                                        tree.get_root(),
                                                        full_path);
    printf("Current commit: %u\n", curr_commit_id - 1);

    if (uf.size())
    {
        puts("Not commited:");
        std::vector<const char *>::iterator vit = uf.begin();

        for (; vit != uf.end(); ++vit)
            puts((*vit));
    }
    else
        puts("No new files were created since your last commit.");
}

//
// Switches back to a previous state of the repository  by given commit id.
//
void checkout(const std::string &path,
              const char *rhs_id)
{
    std::string commit_id(rhs_id);

    std::string commits_path = path_to_commits(path);

    unsigned int curr_verion = 0, last_version = 0;
    get_version(commits_path, curr_verion, last_version);

    if (strcmp(rhs_id, "HEAD") == 0)
        commit_id = std::to_string(last_version);

    unsigned int id = atoi(commit_id.c_str());

    file_map original_map;
    file_map copy_map;

    commit_info(original_map,
                copy_map,
                commits_path,
                id);

    prefix_tree tree(path);
    prefix_tree::iterator root = tree.get_root();
    get_files(path, tree, root);

    std::string curr_path;

    copy_commit_files(original_map,
                      copy_map,
                      root,
                      curr_path);

    update_version(commits_path, id, last_version);
}

//
// Reverts a file to a previous version. If it no longer exists it re-creates it.
//
void revert(const std::string &repo_path,
            const char *commit_id,
            const char *file_path)
{
    std::string commits_path = path_to_commits(repo_path);

    const char *file_name = file_path + 3; //4 is "src" length.

    file_map original_map;
    file_map copy_map; //hash map of the copy files paths and their hashes.

    unsigned int id = atoi(commit_id);

    commit_info(original_map,
                copy_map,
                commits_path,
                id);

    const char *hash = fetch_file_hash(original_map,
                                       repo_path,
                                       file_name);
    if (hash)
    {
        const char *original_file_path = original_map.get_path(hash);
        const char *copy_file_path = copy_map.get_path(hash);

        std::ifstream file_copy(copy_file_path);
        if (file_copy)
        {
            std::ofstream file(original_file_path);
            if (file)
            {
                file << file_copy.rdbuf();
                file.close();
            }
            else
            {
                file_copy.close();
                throw "Failed to create/truncate the given file.";
            }
            file_copy.close();
        }
        else
            throw "Failed to read the given file.";

        std::string message("reverts the file:\"");
        message.append(file_path);
        message.append("\" to its content from commit: ");
        message.append(commit_id);

        make_commit(repo_path, "myGit", message);
    }
    else
    {
        std::cout << "Failed to locate "
                  << file_name + 1
                  << " within commit "
                  << commit_id
                  << ".\n";
    }
}

//
// Returns the path to the commits dir somewhere in the passed in directory.
//If it fails to find the commits dir, throws due to the fact that
//the passed in directory is NOT a repository.
//
std::string path_to_commits(const std::string &path)
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
void commit_info(file_map &original,
                 file_map &copy,
                 std::string path,
                 unsigned int id)
{
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
        //read the original path
        while (info.read(original_path, PATH_LENGTH))
        {
            //read the path to the file copy.
            info.read(copy_path, PATH_LENGTH);
            //read the hash of the file.
            info.read(temp_hash, HASH_LENGTH);

            original_file.set_path(original_path);
            original_file.set_hash(temp_hash);

            copy_file.set_path(copy_path);
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
        puts((*it).get_path());
        puts((*it).get_hash());
    } */
    else
        throw "Failed to open info.bin\n";
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
    to.append(file.get_path());

    if (!prev_committed(original, file, from))
    {

        strcpy(temp_path, to.c_str());
        info.write(temp_path, PATH_LENGTH);

        std::ifstream source(from.c_str(), std::ios::binary);
        std::ofstream dest(to.c_str(), std::ios::binary);
        dest << source.rdbuf();

        dest.close();
        source.close();
    }
    else
    {
        const char *hash = original[from];
        const char *copy_path = copy.get_path(hash);
        info.write(copy_path, PATH_LENGTH);
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
                std::string full_path,
                std::string to)
{
    std::string temp;

    full_path.append(root->directory.c_str());
    file_map::iterator file_it = root->files.begin();
    if (file_it)
    {
        //puts((*file_it).get_path());
        temp = full_path;
        for (; file_it != root->files.end(); ++file_it)
        {
            temp.append((*file_it).get_path());
            commit_file(original,
                        copy,
                        info,
                        temp,
                        to,
                        (*file_it));
            temp = full_path;
        }
    }

    auto folder_it = root->folders.begin();
    for (; folder_it != root->folders.end(); ++folder_it)
    {
        commit_dir(info,
                   original,
                   copy,
                   *(*(folder_it)),
                   full_path,
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

    std::string version_path = path;
    version_path.append("/version.bin");

    std::ifstream version(version_path.c_str(), std::ios::binary);
    if (version)
    {
        version.read(reinterpret_cast<char *>(&id), sizeof(unsigned int));
    }
    else
        throw "Failed to retrieve the last commit id.\n";
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

//
//Fills a vector with names of file that weren't included in the last commit.
//
std::vector<const char *> get_uncommited_files(file_map &last_commit,
                                               prefix_tree::iterator root,
                                               std::string full_path)
{
    static std::vector<const char *> uncommited_files;

    full_path.append(root->directory);

    std::string temp;

    file_map::iterator fit = root->files.begin(); //file iterator.
    const char *hash;
    for (; fit != root->files.end(); ++fit)
    {
        temp = full_path;
        temp.append((*fit).get_path());

        hash = last_commit[temp];
        if (hash)
        {
            if (strcmp(hash, (*fit).get_hash()) != 0)
                uncommited_files.push_back((*fit).get_path());
        }
        else
            uncommited_files.push_back((*fit).get_path());
    }

    auto dit = root->folders.begin(); //directory iterator.
    for (; dit != root->folders.end(); ++dit)
    {
        get_uncommited_files(last_commit,
                             *(*dit),
                             full_path);
    }

    return uncommited_files;
}

//
// Returns the file hash if such a file exists in the current commit dir.
//
const char *fetch_file_hash(file_map &original,
                            const std::string &repo_path,
                            const std::string &file_name)
{
    file_map::iterator fap_it = original.begin(); //file map iterator.

    const char *first_substr = NULL;
    const char *second_substr = NULL;

    for (; fap_it != original.end(); ++fap_it)
    {
        bool found_file = substr_in_path((*fap_it).get_path(),
                                         repo_path,
                                         file_name);

        if (found_file)
        {
            return (*fap_it).get_hash();
        }
    }

    return NULL;
}

//
//  Returns true if we've managed to find the prefix and suffix string in a file path.
//
bool substr_in_path(const char *path,
                    const std::string &repo_path,
                    const std::string &file_name)
{
    size_t original_path_len = strlen(path) - 1;
    size_t repo_path_len = repo_path.length();
    size_t name_len = file_name.length();

    size_t path_counter = 0, name_counter = 0;

    for (size_t c = 0; c < repo_path_len; ++c)
    {
        if (path[c] == repo_path[c % repo_path_len])
            ++path_counter;
        else
            break;
    }

    for (size_t c = 0; c < name_len; ++c)
    {
        if (path[original_path_len - c] == file_name[name_len - (1 + (c % name_len))])
            ++name_counter;
        else
            break;
    }
    if (path_counter == repo_path_len && name_counter == name_len)
        return 1;

    return 0;
}

//
// Gets the current version of the repostory along with the latest version of the repository.
//
void get_version(const std::string path,
                 unsigned int &curr_version,
                 unsigned int &last_version)
{
    std::string version_path = path_to_commits(path);
    version_path.append("/version.bin");

    std::ifstream version(version_path.c_str());

    if (version)
    {
        version.read(reinterpret_cast<char *>(&curr_version), sizeof(unsigned int));
        version.read(reinterpret_cast<char *>(&last_version), sizeof(unsigned int));
    }
    else
        throw "Failed to open version.bin file.\n";
}

//
// Updates the file holding the current and last versions of the repository.
//
void update_version(const std::string &path,
                    const unsigned int &curr_version,
                    const unsigned int &last_version)
{
    std::string version_path = path_to_commits(path);
    version_path.append("/version.bin");

    std::ofstream version(version_path.c_str(), std::ios::trunc);

    if (version)
    {
        version.write(reinterpret_cast<const char *>(&curr_version), sizeof(unsigned int));
        version.write(reinterpret_cast<const char *>(&last_version), sizeof(unsigned int));

        version.close();
    }
    else
        throw "Failed to update the version file.";
}

//
//Copy all the files from the commit directory, discarding any changes that weren't commited before-hand.
//
void copy_commit_files(file_map &original_map,
                       file_map &copy_map,
                       prefix_tree::iterator root,
                       std::string path)
{
    path.append(root->directory);

    std::string temp;

    file_map::iterator fit = root->files.begin(); //file iterator.
    const char *hash = NULL;
    for (; fit != root->files.end(); ++fit)
    {
        temp = path;
        temp.append((*fit).get_path());

        hash = original_map[temp];
        if (hash)
        {
            if (strcmp(hash, (*fit).get_hash()) != 0)
            {
                std::ofstream original_file(temp.c_str(), std::ios::binary);
                if (original_file)
                {
                    std::ifstream copy_file(copy_map.get_path(hash));
                    if (copy_file)
                    {
                        original_file << copy_file.rdbuf();
                        copy_file.close();
                    }
                    else
                        throw "Failed to read the copy file.";

                    original_file.close();
                }
                else
                    throw "Failed to rewrite the original file.";
            }
        }
        else
            std::remove(temp.c_str());
    }

    const char *t = NULL;
    file_map::iterator fap_it = original_map.begin();
    for (; fap_it != original_map.end(); ++fap_it)
    {
        hash = root->files[(*fap_it).get_path()];
        if (!hash)
        {
            std::ofstream original_file((*fap_it).get_path(), std::ios::binary);
            if (original_file)
            {
                t = copy_map.get_path((*fap_it).get_hash());

                std::ifstream copy_file(copy_map.get_path((*fap_it).get_hash()));
                if (copy_file)
                {
                    original_file << copy_file.rdbuf();
                    copy_file.close();
                }
                else
                    throw "Failed to read the copy file.";

                original_file.close();
            }
            else
                throw "Failed to rewrite the original file.";
        }
    }

    auto dit = root->folders.begin(); //directory iterator.
    for (; dit != root->folders.end(); ++dit)
    {
        copy_commit_files(original_map,
                          copy_map,
                          *(*dit),
                          path);
    }
}