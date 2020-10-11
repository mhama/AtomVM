-module(m5).
-export([open/0, show_message/2, button_read/2]).

open() ->
    open_port({spawn, "m5"}, []).

-spec show_message(pid(), string()) -> ok.
show_message(Pid, Msg) ->
    call(Pid, {m5_show_message, Msg}).

-spec button_read(pid(), non_neg_integer()) -> boolean().
button_read(Pid, ButtonIndex) ->
    call(Pid, {m5_button_read, ButtonIndex}).

call(Pid, Msg) ->
    Ref = erlang:make_ref(),
    Pid ! {self(), Ref, Msg},
    receive
        Ret ->
            Ret
    end.
