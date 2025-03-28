    @ Health and Safety Screen
    HealthAndSafetyMainThread:
    .byte 0xf6, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00
    .4byte GroundDataS05StationFile_Text
    changeTileset 0xE3
    pushR14
    MsgEnd 0x163

    .global GroundDataS05StationFile_Text @ 0x826F5F4
    GroundDataS05StationFile_Text:
    .string "../data/ground/ground_data_s05_station.c\0"
    .align 2,0

    HealthAndSafetyMainThreadHeader:
    .byte 0x94, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
    .4byte HealthAndSafetyMainThread

    HealthAndSafety2MainThread:
    .byte 0xf6, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .4byte GroundDataS05StationFile_Text
    pushR14
    changeTileset 0xE3
    StartSceneRunCall 0
    .byte 0x22, 0x01, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    pause 0xB4
    setFlag 4
    .byte 0x3b, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    pause 0xe10
    fadeOut 1 0x1E 0
    endFuncAndScript

    HealthAndSafety2MainThreadHeader:
    .byte 0x90, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00
    .4byte HealthAndSafety2MainThread

    HealthAndSafetyCameraThread: @ 826F6E8
    @ Thread init
    .byte 0xf6, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .4byte GroundDataS05StationFile_Text
    @ Camera stuff
    .byte 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    waitFlag 4
    label 0
    warpToLoc 1 @ Health and Safety w/ Press Button to Continue
    pause 0x14
    warpToLoc 0 @ Health and Safety w/o message
    pause 0x14
    loopLabel 0

    .global gUnknown_826F778
    gUnknown_826F778:
    .byte 0x00, 0x00, 0x01, 0x01
    .byte 15, 11, 0x00, 0x02 @ Initial Camera coordinates
    .4byte HealthAndSafetyCameraThread
    .global gUnknown_826F784
    gUnknown_826F784:
    .4byte HealthAndSafetyMainThreadHeader
    .global gUnknown_826F788
    gUnknown_826F788:
    .4byte HealthAndSafety2MainThreadHeader
    .global gUnknown_826F78C
    gUnknown_826F78C:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
    .4byte gUnknown_826F784
    .global gUnknown_826F7B4
    gUnknown_826F7B4:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
    .4byte gUnknown_826F778
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
    .4byte gUnknown_826F788

    @ Scenes?
    HealthSafetyScenes: @ 826F7DC
    .byte 0x01, 0x00, 0x00, 0x00
    .4byte gUnknown_826F78C
    .byte 0x01, 0x00, 0x00, 0x00
    .4byte gUnknown_826F7B4

    HealthSafetyWaypoints: @ 826F7EC
    .byte 15, 11, 0x00, 0x02, 0x01, 0x01, 0x02, 0x01
    .byte 15, 31, 0x00, 0x02, 0x01, 0x01, 0x02, 0x01

    .global gGroundScript_gs227
    gGroundScript_gs227:
    .byte 0x02, 0x00, 0x00, 0x00
    .4byte HealthSafetyScenes
    .4byte HealthSafetyWaypoints
