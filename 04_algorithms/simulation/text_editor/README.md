# 文本编辑器模拟

[solution.cpp](solution.cpp) 包含完整中文操作说明、原始样例、可运行实现和边界测试。原题来源未提供，规则按用户代码整理；每次调用从空文本开始、不记忆上下移动前的目标列等语义，已在题面明确。

它归入字符串模拟题：一次接收完整操作串，按顺序模拟文本、光标位置和大小写模式，最后返回结果。`Solution` 是题解外壳；本题没有要求设计独立的插入、删除等公开接口，也不要求调用方通过多个接口持续操作同一个编辑器对象，因此放在 `04_algorithms/simulation` 更贴切。

## 保留的结构与局部调整

保留 `Solution`、`find_pre/find_back`、`pos/open` 和原来的上下移动公式。成员字符串 `text` 保存正在编辑的全文，`currentLine` 暂存拆分中的一行，`result` 保存最终返回的各行，以区分编辑状态和返回结果。

- **修复重复调用残留文本**：进入 `StrEdit` 时执行 `text.clear()`。原实现再次调用时光标回到 0，但旧文本仍在，导致新字符插入旧内容。
- **修正注释**：`find_back` 找不到换行时返回文本长度，原注释写成了 -1。
- **简化拆行**：遇到换行保存一行，循环结束后再无条件保存最后一行。空文本和末尾空行自然保留；原实现的末尾空行处理本来正确，这里只是简化。
- **明确大小写操作**：用 `toupper` 和 `!open` 表达转换与切换。此处已限定输入为小写英文字母，在当前环境中可直接传入 `op`，再将返回结果转回 `char`。
- **统一位置比较**：题面约定输入长度小于 INT_MAX，保留 int 下标以使用 -1 哨兵，对 `size()` 明确转换，避免有符号与无符号混用。

## 光标不是“某个字符”

用竖线表示光标，文本为 `ab` 时有三个合法位置：`|ab`、`a|b`、`ab|`，分别对应 pos=0、1、2。

插入发生在 pos，随后 pos 加 1。退格先让 pos 减 1，再删除该位置；Delete 删除 pos，光标不动。左右移动跨过换行符时，也只是移动一个字符位置。

## 上下移动公式

对于向上移动，`previousEnd` 是上一行末尾的换行位置，`previousSeparator` 是上一行前面的换行位置。仅将原来的 pos1、pos2 改为有含义的名字，计算公式不变：

| 含义 | 公式 |
| --- | --- |
| 当前行起点 | previousEnd + 1 |
| 当前列 | pos - previousEnd - 1 |
| 上一行起点 | previousSeparator + 1 |
| 上一行长度 | previousEnd - previousSeparator - 1 |
| 列未越界时的新位置 | (previousSeparator + 1) + (pos - previousEnd - 1) = previousSeparator + pos - previousEnd |
| 列超过上一行长度时的新位置 | previousEnd，即上一行末尾 |

因此 `pos - previousEnd <= previousEnd - previousSeparator` 的比较是对的：它把两边的 -1 抵消了。首行没有上一行，previousEnd==-1 时直接忽略上移。

向下移动同理：`previousEnd` 是当前行前的换行位置，`currentEnd` 是当前行结尾，`nextEnd` 是下一行结尾。下一行起点为 currentEnd+1，长度为 nextEnd-currentEnd-1。当前位置列能放下时，新位置是 currentEnd+pos-previousEnd；否则落在 nextEnd。没有下一行时，currentEnd 等于全文长度。

本题每次按当前列计算。例如第 4 列移到只有 1 个字符的行后，光标变成第 1 列；再次下移使用第 1 列，不会恢复第 4 列。

## 输出与验证

空文本输出 `[""]`，一次换行输出 `["", ""]`。测试给每一行加引号，避免直接用空格打印时看不出空行。

内置测试覆盖原始操作序列、同列和短行移动、首尾行、连续空行、两种跨行删除、左右跨行、大小写切换及重复调用。算法最坏 O(n²) 时间、O(n) 空间；未提供需要更复杂数据结构的性能约束。

从仓库根目录编译运行：

```powershell
New-Item -ItemType Directory -Force .\build | Out-Null
g++ -std=c++17 -Wall -Wextra -pedantic .\04_algorithms\simulation\text_editor\solution.cpp -o .\build\text_editor.exe
.\build\text_editor.exe
```
