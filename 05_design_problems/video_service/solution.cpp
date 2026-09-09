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

       (释放时间 - 分配时间) * 请求类型的单位时间费用

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
service.AllocateChannel(5, 110, 1);  // 返回 false，类型 1 和 2 都已满
service.QueryChannel(108);           // 返回 2
service.FreeChannel(13, 108);        // 返回 (13 - 3) * 15 = 150

示例 2：
VideoService service({1, 1, 1}, {10, 20, 30});
service.AllocateChannel(0, 101, 0);  // 返回 true，实际分配类型 0
service.AllocateChannel(0, 102, 0);  // 返回 true，实际分配类型 1
service.AllocateChannel(0, 103, 0);  // 返回 true，实际分配类型 2
service.FreeChannel(5, 101);         // 返回 50；用户 103 从类型 2 迁移到类型 0
service.QueryChannel(103);           // 返回 0
*/

#include <array>
#include <iostream>

using namespace std;

class ChannelInfo {
public:
    int cap;//总的容量
    int inUse;//当前使用情况(occupied_numbers)
    int fee;//单位时间费用
};

class UserInfo {
public:
    int flg;//当前是否被成功分配
    int id;//成功分配的id号
    int reqType;//请求频道类型
    int time;//时间(包含分配开始时间以及结束时间)
    int realType;//真实的频道分配类型
};

class VideoService {
public:
    VideoService(const array<int, 3>& channels, const array<int, 3>& charge)//将频道信息赋给全局变量（传出去）
    {
        for (int i = 0; i < channels.size(); i++) {
            chInfo[i].cap = channels[i];
            chInfo[i].fee = charge[i];
        }
    }

    bool AllocateChannel(int time, int userId, int videoType)
    {
        int realType = videoType;
        if (getChannel(time, videoType, realType)) {
            user[userId].flg = 1;//1表示已经分配成功
            user[userId].realType = realType;
            user[userId].reqType = videoType;
            user[userId].time = time;
            return true;
        }
        return false;
    }

    int FreeChannel(int time, int userId)
    {
        if (user[userId].flg == 0) {
            return -1;
        }
        int fee = chInfo[user[userId].reqType].fee;//单位时间费用，按照请求时间计费
        int ret = (time - user[userId].time) * fee;//总的费用
        user[userId].flg = 0;//维护该类型信息为0，表示已经被释放掉
        FreeUper(user[userId].realType);//释放掉真实占用频道
        return ret;
    }

    int QueryChannel(int userId)
    {
        if (user[userId].flg == 0) {
            return -1;
        }
        return user[userId].realType;//返回真实占用频道类型
    }

    bool getChannel(int time, int videoType, int &realType)
    {
        // 从低往高找可用通道
        for (int i = videoType; i < 3; i++) {
            if (chInfo[i].cap > chInfo[i].inUse) {
                chInfo[i].inUse++;//当前用户使用的频道数量增加1
                realType = i;
                return true;
            }
        }
        return false;
    }

    void FreeUper(int type)
    {
        chInfo[type].inUse--;
        // 只释放了一个通道 找到一个申请类型 <释放类型的用户
        int id = -1;
        for (int i = 1; i < user.size(); i++) {
            if (user[i].flg != 1) {
                continue;
            }
            // 占用带宽高于释放通道的带宽  所申请带宽不高于释放通道的带宽
            if (user[i].realType > type  && user[i].reqType <= type) {
                // 优先选择占用带宽最高的用户；如果还有多个，则选择其中 userId 最小的 由于id按照从小到大排列 默认满足id最小
                if (id == -1 || (user[i].realType > user[id].realType)) {
                    id = i;
                }
            }
        }
        // 找到占用的user 修改真实使用通道 并且继续释放
        if (id != -1) {
            int realType = user[id].realType;
            user[id].realType = type;
            chInfo[type].inUse++;
            FreeUper(realType);
        }
    }

    array<ChannelInfo, 3> chInfo = {};
    array<UserInfo, 1001> user = {};
};

int main(int argc, char const *argv[])
{
    VideoService V({8, 1, 1}, {10, 15, 30});
    //V.VideoService([8, 1, 1], [10, 15, 30]);
    cout<<V.AllocateChannel(3, 107, 1)<<endl;
    cout<<V.AllocateChannel(3, 108, 1)<<endl;
    cout<<V.AllocateChannel(5, 110, 1)<<endl;
    cout<<V.QueryChannel(108)<<endl;
    cout<<V.FreeChannel(13, 108)<<endl;
    return 0;
}

/*收获点：
1. 初始化时一般将给定的信息传出来，即将信息赋值给一个全局变量
2. 如果给定的信息包含多组不同的数据，那么使用一个class将其包含
3. 使用辅助函数实现代码
*/
