#!/usr/bin/python3

#1RecommendedBooks
#2wangguilin
#3github
#4openSourceCode
#5houjie

import os
# import commands

res = {
    # "Blogs": "git@github.com:Hsurpass/Blogs.git",
    # "ElegantTest": 'git@github.com:Hsurpass/ElegantTest.git',
    # 'houjie': 'git@github.com:Hsurpass/houjie.git',
    # 'log4js-demo': 'git@github.com:Hsurpass/log4js-demo.git',
    # 'mocha_integrative_test': 'git@github.com:Hsurpass/mocha_integrative_test.git',
    'plan': 'git@github.com:Hsurpass/plan.git',
    # 'wangguilin': 'git@github.com:Hsurpass/wangguilin.git',
    # 'winston_demo': 'git@github.com:Hsurpass/winston_demo.git'
}

openSourceRes = {
    "cgdb": "git@github.com:Hsurpass/cgdb.git",
    # "cgdb-manual-in-chinese": "git@github.com:leeyiw/cgdb-manual-in-chinese.git",
    # "CMake-Cookbook": "git@github.com:xiaoweiChen/CMake-Cookbook.git",
    # "cmake-examples": "git@github.com:Hsurpass/cmake-examples.git",
    # "C-Plus-Plus": "git@github.com:TheAlgorithms/C-Plus-Plus.git",
    # "CPlusPlusThings": "git@github.com:Light-City/CPlusPlusThings.git",
    # "CppTemplateTutorial": "git@github.com:wuye9036/CppTemplateTutorial.git",
    # "design-patterns-cpp": "git@github.com:JakubVojvoda/design-patterns-cpp.git",
    # "fcgilib": "git@github.com:Hsurpass/fcgilib.git",
    # "googletest": "git@github.com:google/googletest.git",
    # "hello-algorithm": "git@github.com:geekxh/hello-algorithm.git",
    # "libevent-book": "git@github.com:nmathewson/libevent-book.git",
    # "libhv": "git@github.com:ithewei/libhv.git",
    # "muduo": "git@github.com:Hsurpass/muduo.git",
    # "muduo-tutorial": "git@github.com:Hsurpass/muduo-tutorial.git",
    # "MyTinySTL": "git@github.com:Alinshans/MyTinySTL.git",
    # "pierced": "git@github.com:open-dingtalk/pierced.git",
    # "redis-4.0.14": "git@github.com:Hsurpass/redis-4.0.14.git",
    # "redis-5.0.14": "git@github.com:Hsurpass/redis-5.0.14.git",
    # "redis-6.2.7": "git@github.com:Hsurpass/redis-6.2.7.git",
    # "spawn-fcgi-c": "git@github.com:Hsurpass/spawn-fcgi-c.git",
    # "Tinyhttpd": "git@github.com:Hsurpass/Tinyhttpd.git",
    # "TinyWebServer": "git@github.com:qinguoyi/TinyWebServer.git",
    # "Typora_Free_Download": "git@github.com:ydsuper/Typora_Free_Download.git"
}

def fetchRes(k, v):
     # print(os.path.exists('Blogs'))
    os.chdir(k)
    # print(os.path.abspath('.'))
    print('----------->Enter {0}'.format(k))

    os.system('git fetch')
    os.system('git rebase')
    # print("git update %s succ " % k)
            
    os.chdir('..')
    # print(os.path.abspath('.'))
    print("Leave {0}<------------".format(k))

def cloneRes(k, v):
    print('>>>>>>>>>>>>>>>start clone {0}'.format(k))
    os.system('git clone {0}'.format(v))
    print('finish clone {0}<<<<<<<<<<<<<<<<<<'.format(k))

def update_repository():
    for k,v in res.items():
        if os.path.exists(k):
           fetchRes(k, v)
        else:
           cloneRes(k, v)

def update_openSource_repository():
    dir = '4openSourceCode'
    
    print(os.path.abspath('.'))
    os.chdir('..')
    print(os.path.abspath('.'))
    
    if(not os.path.exists(dir)):
        os.mkdir(dir)
    
    os.chdir(dir)
    print(os.path.abspath('.'))

    for k,v in openSourceRes.items():
        if os.path.exists(k):
            fetchRes(k, v)
        else:
            cloneRes(k, v)


if __name__ == "__main__":
    update_repository()
    update_openSource_repository()
