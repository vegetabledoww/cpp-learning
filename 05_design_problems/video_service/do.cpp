/*
题目：视频频道资源管理系统

某视频服务提供 3 种频道，频道类型依次为 0、1、2，类型越大表示频道等级越高。
channels[i] 表示类型 i 的频道总容量，charge[i] 表示类型 i 的单位时间费用。

请实现 VideoService 类，完成频道分配、释放和查询功能。

1. VideoService(channels, charge)
   使用 channels 和 charge 初始化 3 种频道的容量及费用。

2. AllocateChannel(time, userId, videoType)
   为用户 userId 申请类型 videoType 的频道。
   优先分配请求类型；如果该类型已满，则按照类型从低到高依次寻找更高类型的频道。
   分配成功返回 true，并记录用户的申请时间、请求类型和实际占用类型；
   如果没有可用频道，返回 false。

3. FreeChannel(time, userId)
   释放用户当前实际占用的频道。如果用户没有成功分配频道，返回 -1。
   否则返回本次使用费用：

       (释放时间 - 分配时间) * 请求类型的单位时间费用(不是实际占用频道的单位时间)

   释放频道后，需要尽量让正在占用较高类型频道的用户迁移到刚释放的较低类型频道：
   - 该用户的请求类型必须不高于刚释放的频道类型；
   - 优先迁移当前实际占用类型最高的用户；
   - 如果实际占用类型相同，优先迁移 userId 较小的用户；
   - 用户迁移后，其原来占用的较高类型频道也被释放，并继续按照相同规则处理。

4. QueryChannel(userId)
   如果用户正在使用频道，返回其实际占用的频道类型；否则返回 -1。

题目保证：
- 1 <= userId <= 1000，0 <= videoType <= 2；
- time 按非递减顺序给出，释放时间不早于分配时间；
- 同一用户只有在未占用频道时才会再次申请。

示例 1：
VideoService service({8, 1, 1}, {10, 15, 30});
service.AllocateChannel(3, 107, 1);  // 返回 true，实际分配类型 1
service.AllocateChannel(3, 108, 1);  // 返回 true，类型 1 已满，实际分配类型 2
service.AllocateChannel(5, 110, 1);  // 返回 false
service.QueryChannel(108);           // 返回 2
service.FreeChannel(13, 108);        // 返回 150

示例 2：
VideoService service({1, 1, 1}, {10, 20, 30});
service.AllocateChannel(0, 101, 0);  // 返回 true，实际分配类型 0
service.AllocateChannel(0, 102, 0);  // 返回 true，实际分配类型 1
service.AllocateChannel(0, 103, 0);  // 返回 true，实际分配类型 2
service.FreeChannel(5, 101);         // 返回 50；用户 103 从类型 2 迁移到类型 0
service.QueryChannel(103);           // 返回 0
*/
#include <array>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

struct UserInfo
{
    int startTime;//分配开始时间
    int requestType;//用户请求的频道类型，用于计费
    int actualType;//用户实际占用的频道类型
    bool active;//当前是否正在使用频道（一结束就不再使用了）
};

class VideoService
{
public:
    vector<int>caps;//最大容量
    vector<int>charges;//每隔channel的收费情况
    vector<int>occ = {0,0,0};//3种频道当前分别被占用的数量
    map<int,UserInfo>table;//userId --> 用户的完整使用信息

    VideoService(const array<int, 3> &channels,
                 const array<int, 3> &charge)
    {
        for (int i = 0; i < 3; i++)
        {
            caps.push_back(channels[i]);
            charges.push_back(charge[i]);
        }
    }

    bool AllocateChannel(int time, int userId, int videoType)
    {
        int actualType = -1;
        //从请求类型开始，向更高类型寻找空闲频道
        for (int type = videoType; type < 3; type++)
        {
            if (occ[type] < caps[type])//如果该类型没满，则申请该类型的频道
            {
                actualType = type;
                break;
            }
        }

        //所有可用类型都满了，不修改任何状态
        if (actualType == -1)
            return false;
        UserInfo info;
        info.startTime = time;
        info.requestType = videoType;
        info.actualType = actualType;
        info.active = true;

        occ[actualType]++;
        table[userId] = info;
        return true;
    }

    int FreeChannel(int time, int userId)
    {
        auto it = table.find(userId);
        //从没开始过或者已经结束
        if (it == table.end() || !it->second.active)
            return -1;

        UserInfo &info = it->second;
        int result = (time - info.startTime) * charges[info.requestType];
        int freeType = info.actualType;

        info.active = false;
        info.actualType = -1;//-1代表没占用
        occ[freeType]--;

        MoveUsersAfterFree(freeType);
        return result;
    }

    int QueryChannel(int userId)
    {
        auto it = table.find(userId);
        if (it == table.end() || !it->second.active)
            return -1;
        return it->second.actualType;
    }

    // 将一个最合适的用户迁移到 freeType。
    // 返回该用户原来占用的频道类型；没有用户可以迁移时返回 -1。
    int MoveOneUserToFreeType(int freeType)
    {
        int candidateId = -1;
        int candidateActualType = -1;
        //寻找可以迁移到当前空闲类型的最优用户
        for (auto it = table.begin(); it != table.end(); it++)
        {
            int currentUserId = it->first;
            UserInfo &currentUser = it->second;
            if (!currentUser.active)//当前用户并没有占用频道（这种情况通常是已经发送了结束时间了）
                continue;
            //是否能够移动条件：当前真实频道大于释放频道（能否降）且请求频道小于等于释放频道（能否接）
            bool canMove = currentUser.actualType > freeType &&
                           currentUser.requestType <= freeType;
            if (!canMove)
                continue;
            //判断当前用户是不是更好的降级候选者
            bool isBetter = candidateId == -1 ||
                            currentUser.actualType > candidateActualType ||
                            (currentUser.actualType == candidateActualType &&
                             currentUserId < candidateId);
            if (isBetter)
            {
                candidateId = currentUserId;
                candidateActualType = currentUser.actualType;
            }
        }

        if (candidateId == -1)
            return -1;

        int oldType = table[candidateId].actualType;
        table[candidateId].actualType = freeType;
        occ[freeType]++;
        occ[oldType]--;
        return oldType;
    }

    void MoveUsersAfterFree(int freeType)
    {
        // 类型 0 空闲时先尝试填补；如果因此释放了类型 1，再继续填补类型 1。
        if (freeType == 0)
            freeType = MoveOneUserToFreeType(0);

        // 类型 1 空闲时只可能让类型 2 的用户降下来；类型 2 空闲时无需处理。
        if (freeType == 1)
            MoveOneUserToFreeType(1);
    }
};

int main()
{
    cout << "Example 1:\n";
    VideoService service({8, 1, 1}, {10, 15, 30});

    cout << "Allocate user 107, expected=1, actual="
         << service.AllocateChannel(3, 107, 1) << '\n';
    cout << "Allocate user 108, expected=1, actual="
         << service.AllocateChannel(3, 108, 1) << '\n';
    cout << "Allocate user 110, expected=0, actual="
         << service.AllocateChannel(5, 110, 1) << '\n';
    cout << "Query user 108, expected=2, actual="
         << service.QueryChannel(108) << '\n';
    cout << "Free user 108, expected=150, actual="
         << service.FreeChannel(13, 108) << '\n';

    cout << "\nExample 2:\n";
    VideoService service2({1, 1, 1}, {10, 20, 30});

    cout << "Allocate user 101, expected=1, actual="
         << service2.AllocateChannel(0, 101, 0) << '\n';
    cout << "Allocate user 102, expected=1, actual="
         << service2.AllocateChannel(0, 102, 0) << '\n';
    cout << "Allocate user 103, expected=1, actual="
         << service2.AllocateChannel(0, 103, 0) << '\n';
    cout << "Free user 101, expected=50, actual="
         << service2.FreeChannel(5, 101) << '\n';
    cout << "Query user 103, expected=0, actual="
         << service2.QueryChannel(103) << '\n';

    cout << "\nChain move test:\n";
    VideoService service3({1, 1, 1}, {10, 20, 30});
    service3.AllocateChannel(0, 201, 0); // 实际占用类型 0
    service3.AllocateChannel(0, 202, 0); // 实际占用类型 1
    service3.AllocateChannel(0, 203, 1); // 实际占用类型 2
    service3.FreeChannel(1, 201);        // 202 降到 0，随后 203 降到 1
    cout << "Query user 202, expected=0, actual="
         << service3.QueryChannel(202) << '\n';
    cout << "Query user 203, expected=1, actual="
         << service3.QueryChannel(203) << '\n';

    return 0;
}
