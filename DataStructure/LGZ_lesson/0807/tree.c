#include "LinkTree.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

void ExploreDirectory(const char *path, LTNode *parentNode)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        return;
    }
    struct dirent *entry = readdir(dir);
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        LTNode *fileNode = CreateTreeNode(entry->d_name);
        ConnectBranch(parentNode, fileNode);

        if (entry->d_type == 4)
        {
            char filePath[100] = {0};
            strcpy(filePath, path);
            strcat(filePath, "/");
            strcat(filePath, entry->d_name);
            ExploreDirectory(filePath, fileNode);
        }

        // entry = readdir(dir);
    }
    closedir(dir);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("invalid input numbers!\n");
        return 0;
    }

    LTree FileTree;
    InitTree(&FileTree);

    FileTree.root->data = argv[1];
    ExploreDirectory(argv[1], FileTree.root);

    Travel(&FileTree);

    

    return 0;
}