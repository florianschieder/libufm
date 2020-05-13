LibUFM
==
_libufm_ is a project providing a cross-platform backend for the _UFM_ (Universal File Manager) project.

History
--
At the very beginning of the Universal File Manager project, a pure Windows project - _WFM_ (Windows File Manager) - was started. It was just one repository and one Visual C++ project, but the application and toolkit source files have already been separated back then. After some time of development, I decided to divide _WFM_ and its toolkit into two separate repositories. The reason: Even though the both belong together and one could not work or would be useless without the other, the toolkit's features could not only be integrated into other projects of mine or foreign ones. After some work of abstraction, the features - and so the whole _UFM_ project - could also be ported to other Desktop platforms. With this concept, the UFM project was born.

Components
--
The _libufm_ repository consists of two components:
- _cppbul_ (Cross-Platform PureBasic Utility Layer): According to the name, it's written in PureBasic which is a proprietary, cross-platform BASIC language. Common tasks are cross-platform features like input boxes or more complex I/O features which would cause larger dependencies in the main component.
- _libufm_: The "main" component which wraps up platform-specific and _cppbul_ features. _libufm_ requires all components to be built to work properly, but _libufm_ is the only component which must be included directly into UFM or other projects.
