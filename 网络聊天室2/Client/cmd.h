//指令
#define   USERREGISTER        1001    //注册标志
#define   LOGIN               1002    //登录
#define   ADMLOGIN            1003    //管理员用户登录
#define   USERLOGIN           1004    //普通用户登录
#define   CHATONE             1005    //私聊
#define   CHATALL             1006    //群聊
#define   SEARCHONLINEUSER    1007    //查看在线用户
#define   ADMREQUEST          1008    //申请成为管理员
#define   LOGOFFUSER          1009    //踢出在线用户
#define   SLIENCEUSER         1010    //禁言
#define   UNBANUSER           1011    //解禁
#define   SENDFILE            1012    //发送文件



//成功
#define    REGSUCCESS         2001    //注册成功
#define    SAVESUCCESS        2002   //保存用户的数据成功
#define    LOGINSUCCESS       2003   //登录成功
#define    ADMSUCCESS         2004   //请求管理员成功
#define    LOGOFFSUCCESS      2005   //成功踢下线
#define    SLIENCESUCCESS     2006   //禁言成功
#define    UNBANSUCCESS       2007   //解禁成功（服务器告诉管理员）
#define    HAVEBINUNBAN       2008   //解禁成功（服务器告诉被禁言用户）
#define    RECVSUCCESS        2009   //接收文件成功


//失败
#define    CREATEERROR        3001    //创建数据库失败
#define    SAVEERROR          3002    //用户已经存在
#define    OPTABLEaERROR      3003    //打开表失败
#define    INSERTERROR        3004     //插入失败
#define    LOGINERROR         3005     //账号或者密码不存在
#define    SENDONEERROR       3006     //私聊发送失败
#define    REFUSQADMREQUEST   3007    //拒绝管理员请求
#define    SQLITEREFUSEADM    3008    //同意管理员数据库操作失败
#define    ADMACCOUNT         3009    //踢出管理员失败
#define    SLIENCEFAIL        3010     //禁言失败
#define    SLIENCEUSERERROR   3011     //禁言用户不存在
#define    SLIENCEADM         3012     //禁言管理员失败
#define    HAVENTBENBAN       3013     //该用户没有被禁言
#define    UNBANSERERROR      3014     //解禁用户不存在
#define    HAVELOGIN          3015     //用户已经登录
#define    FILEERROR          3016     //发送文件的用户不存在或者不在线
#define    READERROR          3017     //文件读取失败
#define    REPEATSILENCE      3018     //该用户已经被禁言