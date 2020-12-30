import os
import time
from os.path import join as join_path

dir_path = r"empty_string"
extension = ".mkv"


def findOccurrences(s, ch):
    return [i for i, letter in enumerate(s) if letter == ch]


def chose_dirPath():
    global dir_path
    cur_dirPath = os.path.dirname(os.path.realpath(__file__))
    print("##################################################################")
    print("-Current dir_path:  \"{}\"".format(cur_dirPath))
    print("-Built-in dir_path: \"{}\"\n".format(dir_path))

    print("Select the method to chose the dir_path:\n",
          " 0)Current dir path\n",
          " 1)Built-in dir path\n",
          " 2)Enter manually dir_path")
    print("Enter the selection:", end="")
    choice = input()

    if choice == '0':
        dir_path = cur_dirPath
    elif choice == '2':
        print("Not supported.\nExit!")
        exit(-1)
    else:
        print("Input \"{}\" not valid".format(choice))
        print("EXIT!")
        exit(-1)

    print("##################################################################\n")


if __name__ == "__main__":
    
    chose_dirPath()
    print("Dir selected:", dir_path)

    all_file = os.listdir(dir_path)
    # filter only the files with a given extension
    to_modify = list(filter(lambda x: x[-4:] == extension, all_file))

    new_fileNames = {}

    for idx, file_name in enumerate(to_modify):  # TO MODIFY
        occ = findOccurrences(file_name, " ")
        if(len(occ) > 2):
            new_fileNames[file_name] = file_name[:occ[2]]+extension

    # Show the pairs (old_fileName, new_fileName)
    time.sleep(2)
    print("\nChanged file names:")
    for pair in new_fileNames.items():
        print(pair)

    # Rename all file
    print("\nMake the changes? ", end="")
    if(input() == 'yes'):
        for old, new in new_fileNames.items():
            os.rename(join_path(dir_path, old), join_path(dir_path, new))
        print("Files renamed!")
    else:
        print("EXIT")
