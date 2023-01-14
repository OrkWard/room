### 图形学大作业

基本要求：（共 35 分，每实现一个项目满分得 5 分）

1. 具有基本体素（立方体、球、圆柱、圆锥、多面棱柱、多面棱台）的建模表达能力；
2. 具有基本三维网格导入导出功能（建议 OBJ 模式）；
3. 具有基本材质、纹理的显示和编辑能力；
4. 具有基本几何变换功能（旋转、平移、缩放等）；
5. 基本光照模型要求、并实现基本的光源编辑（如调整光源的位置，光强等参数）；
6. 能对建模后场景进行如 Zoom In/Out，Pan，Orbit，Zoom To Fit 等观察功能；
7. 能够提供屏幕截取/保存功能。

额外要求：（每增加一个额外项目的效果，额外增加分数，但每项满分为 5 分，严格要求，直至加满至 40 分）

1. 具有 NURBS 曲面建模能力；
2. 漫游时可实时碰撞检测；
3. 光照明模型细化，可任选实现实时阴影、caustic、全局光照明（光线追踪）、辐射度等
4. 采用 HTML5/IOS/Android 移动平台实现

### TODOLIST
- [x] 创建基本形状
  > 打开一个新窗口，里面展示了可创建的各种形状：立方体、球、圆柱、圆锥、棱柱、棱台；  
  > 六个形状以 3D 旋转状态从侧上方进行展示；同时实现基础光照  
  > 鼠标移到任一物体上方（box）时，展示边框
- [x] 观察
  > 鼠标滚轮控制缩放  
  > shift + 中键平移
  > 中键旋转
- [ ] 平移、旋转、缩放物体
  > 维护一个列表，用于存储已创建的物体  
  > 选择物体后，在主窗口按下对应的按键进行平移、旋转、缩放、聚焦  
- [ ] 材质、纹理的显示和编辑能力
  > 右键物体列表，打开材质、纹理编辑窗口  
  > 上下两栏
- [ ] 三维网格导入、导出功能 
  > 选中的物体通过按键导出，导出时有提示  
  > 通过按键打开 Windows 文件选择器导入 obj 文件
- [ ] 光源编辑
  > 默认有一个全局点光源  
  > 可选择开关的中心在摄像机位置的手电筒