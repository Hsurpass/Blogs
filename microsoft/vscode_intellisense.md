



1.   创建c_cpp_properties.json (ctrl + shift + p)

     ![Command Palette filtered on C/C++ Edit Configurations command](image/edit-configurations-ui.png)

2.   配置c_cpp_properties.json

     ```json
     {
         "configurations": [
             {
                 "name": "Linux",
                 "includePath": [
                     "${workspaceFolder}/**"
                 ],
                 "defines": [],
                 "compilerPath": "/usr/bin/gcc",
                 "cStandard": "c17",
                 "cppStandard": "c++20",
                 "intelliSenseMode": "linux-clang-x64",
                 "compileCommands": "${workspaceFolder}/build/compile_commands.json"
             }
         ],
         "version": 4
     }
     ```

     

     

# reference

[Configure C/C++ IntelliSense (visualstudio.com)](https://code.visualstudio.com/docs/cpp/configure-intellisense)

[c_cpp_properties.json reference (visualstudio.com)](https://code.visualstudio.com/docs/cpp/c-cpp-properties-schema-reference)

[Get Started with C++ and Windows Subsystem for Linux in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-wsl#_cc-configurations)