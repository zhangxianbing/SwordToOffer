<!--
 * @Author: zhangxianbing
 * @Date: 2019-08-11 11:29:12
 * @LastEditors: zhangxianbing
 * @LastEditTime: 2019-08-12 21:12:10
 * @Description: file content
 -->

思考1：很多时候，如果依赖各种别人做好的动图或写好的代码来理解算法，并不能很好的锻炼自己的思维！

从leetcode摘出题目信息后正则替换
```
^(\d*)\s\n(.*)\n.*
// LC$1. $2\nnamespace LC$1 {} // namespace LC$1\n
```
为增强视图效果，建议安装Better-Comment插件，setting.json里添加：
```json
       "better-comments.tags": [
        {
            "tag": "!",
            "color": "#FF0000",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "@",
            "color": "#FF8C00",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "#",
            "color": "#BBBB23",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "$",
            "color": "#48BB31",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "%",
            "color": "#0070BB",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "^",
            "color": "#19CAAD",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "&",
            "color": "#8A2BE2",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "*",
            "color": "#98C379",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "+",
            "color": "#191970",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "-",
            "color": "#872657",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "?",
            "color": "#F0E68C",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": ">",
            "color": "#FFFF00",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "<",
            "color": "#00FF00",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "|",
            "color": "#FFC0CB",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "//",
            "color": "#474747",
            "strikethrough": true,
            "backgroundColor": "transparent"
        },
        {
            "tag": "/",
            "color": "#3D9140",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "todo",
            "color": "#00FF00",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "lc",
            "color": "#FF8C00",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "fatal",
            "color": "#FF0000",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "error",
            "color": "#FF8C00",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "warning",
            "color": "#BBBB23",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "info",
            "color": "#48BB31",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "debug",
            "color": "#0070BB",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "verbose",
            "color": "#19CAAD",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "assert",
            "color": "#8A2BE2",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "note",
            "color": "#F0E68C",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
        {
            "tag": "注",
            "color": "#F0E68C",
            "strikethrough": false,
            "backgroundColor": "transparent"
        },
    ],
```