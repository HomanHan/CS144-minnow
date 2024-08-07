Stanford CS 144 Networking Lab
==============================

These labs are open to the public under the (friendly) request that to
preserve their value as a teaching tool, solutions not be posted
publicly by anybody.

Website: https://cs144.stanford.edu

To set up the build system: `cmake -S . -B build`

To compile: `cmake --build build`

To run tests: `cmake --build build --target test`

To run speed benchmarks: `cmake --build build --target speed`

To run clang-tidy (which suggests improvements): `cmake --build build --target tidy`

To format code: `cmake --build build --target format`

---

## check start 姿势

1. `git checkout -b check{x}` ———— 创建新开发分支
2. `git fetch CS144` ———— 获取CS144最新情报
3. `git merge CS144/check{x}` ———— 从CS144官方仓库获取check x代码（2+3直接替换为`pull`也可）
4. `git push origin check{x}` ———— 在origin远程仓库添加新分支
5. `git branch --set-upstream-to=origin/check1` ———— 将本地check{x}分支与origin/check{x}分支捆绑

基本理念：不同开发阶段(check 0,1,2...)使用不同分支，每一个新分支需要先从CS144官方仓库merge下来，再同步到origin相应分支。
