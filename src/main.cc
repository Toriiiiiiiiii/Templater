#include <iostream>
#include <cstdio>
#include <string>

#include "arguments.h"

static const std::string templatePath = "~/.config/templater/templates/";

void printUsage(char* executablePath) {
    fprintf(stderr, "%s <project_name> <language>\n", executablePath);
}

int main(int argc, char **argv) {
    std::vector<ArgumentTemplate> parameters = {
        ArgumentTemplate{ARG_REQUIRED | ARG_POSITIONAL, "", "projectName"},
        ArgumentTemplate{ARG_REQUIRED | ARG_POSITIONAL, "", "languageName"}
    };

    ArgumentParser *parser = new ArgumentParser(argc, argv, parameters);

    std::vector<Argument> args = {};
    bool parseResult = parser->parseArguments(args);
    if(!parseResult) {
        printUsage(argv[0]);
        return 1;
    }

    Argument projectNameArgument = parser->getArgByName(args, "projectName");
    Argument languageNameArgumetn = parser->getArgByName(args, "languageName");

    std::string projectName = projectNameArgument.value;
    std::string languageName = languageNameArgumetn.value;

    printf("Creating project '%s' using language template '%s'...\n", projectName.c_str(), languageName.c_str());

    std::string createProjectDirectoryCommand = "mkdir " + projectName;

    system(createProjectDirectoryCommand.c_str());

    std::string copyTemplateFilesCommand = "cp -rf " + templatePath + languageName + "/* " + projectName;

    int result = system(copyTemplateFilesCommand.c_str());
    if(result != 0) return result;

    delete parser;
    return 0;
}