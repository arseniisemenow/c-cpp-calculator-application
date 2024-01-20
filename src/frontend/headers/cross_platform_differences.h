#ifndef CROSSPLATFORMDIFFERENCES_H
#define CROSSPLATFORMDIFFERENCES_H

#if __APPLE__
#define DEFAULT_OPEN_COMMAND "open -t "
#elif __linux__
#define DEFAULT_OPEN_COMMAND "xdg-open "
#elif __unix__
#define DEFAULT_OPEN_COMMAND "open -t "
#endif

#endif // CROSSPLATFORMDIFFERENCES_H
