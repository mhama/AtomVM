-module(m5_message).
-export([start/0]).

start() ->
    M5 = m5:open(),
    m5:show_message(M5, "Hey!! I'm here! Are you hear me?"),
    loop(M5, off).

loop(M5, off) ->
    for(1, 100, fun() ->
        BtnA = m5:button_read(M5, 0),
        BtnB = m5:button_read(M5, 1),
        BtnC = m5:button_read(M5, 2),
        m5:show_message(M5, io_lib:format("A:~p B:~p C:~p  Hello Erlang World! ", [BtnA, BtnB, BtnC])),
        timer:sleep(50)
    end),
    console:puts("hello blink loop off!~n"),
    timer:sleep(1000),
    loop(M5, on);

loop(M5, on) ->
    BtnA = m5:button_read(M5, 0),
    m5:show_message(M5, io_lib:format("button:~p Hello AtomVM World! ", [BtnA])),
    %%m5:show_message(M5, "Hello AtomVM World2!"),
    console:puts("hello blink loop on!~n"),
    timer:sleep(1000),
    loop(M5, off).

for(End, End, F) ->
    [F()];
for(Start, End, F) ->
    [F()|for(Start+1, End, F)].
