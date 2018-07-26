[@bs.scope "TimePickerAndroid"] [@bs.module "react-native"]
external timeSet : string = "timeSetAction";

[@bs.scope "TimePickerAndroid"] [@bs.module "react-native"]
external dismissed : string = "dismissedAction";

type response = {
  hour: int,
  minute: int,
};

type mode =
  | Clock
  | Spinner
  | Default;

type action =
  | Dismissed
  | Set(response);

type optsJs = {
  .
  "hour": Js.Nullable.t(int),
  "minute": Js.Nullable.t(int),
  "is24Hour": Js.Nullable.t(bool),
  "mode": string,
};

type responseJs = {
  .
  "action": string,
  "hour": int,
  "minute": int,
};

let action = resp =>
  if (resp##action == timeSet) {
    Set({hour: resp##hour, minute: resp##minute});
  } else if (resp##action == dismissed) {
    Dismissed;
  } else {
    failwith(
      "Unknown action received from TimePickerAndroid. Please report this in the bs-react-native repository",
    );
  };

[@bs.scope "TimePickerAndroid"] [@bs.module "react-native"]
external _open : optsJs => Js.Promise.t(responseJs) = "open";

let open_ = (~hour=?, ~minute=?, ~is24Hour=?, ~mode=Default, ()) =>
  _open({
    "hour": Js.Nullable.fromOption(hour),
    "minute": Js.Nullable.fromOption(minute),
    "is24Hour": Js.Nullable.fromOption(is24Hour),
    "mode":
      switch (mode) {
      | Default => "default"
      | Clock => "clock"
      | Spinner => "spinner"
      },
  })
  |> Js.Promise.then_((resp: responseJs) =>
       resp |> action |> Js.Promise.resolve
     );
