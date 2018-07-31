[@bs.scope "TimePickerAndroid"] [@bs.module "react-native"]
external timeSet : string = "timeSetAction";

[@bs.scope "TimePickerAndroid"] [@bs.module "react-native"]
external dismissed : string = "dismissedAction";

type response = {
  hour: int,
  minute: int,
};

[@bs.deriving jsConverter]
type mode = [ | `clock | `spinner | `default];

type action =
  | Dismissed
  | Set(response);

[@bs.deriving abstract]
type optsJs = {
  hour: Js.Nullable.t(int),
  minute: Js.Nullable.t(int),
  is24Hour: Js.Nullable.t(bool),
  mode: string,
};

[@bs.deriving abstract]
type responseJs = {
  action: string,
  hour: int,
  minute: int,
};

let actionHandler = resp =>
  if (actionGet(resp) == timeSet) {
    Set({hour: hourGet(resp), minute: minuteGet(resp)});
  } else if (actionGet(resp) == dismissed) {
    Dismissed;
  } else {
    failwith(
      "Unknown action received from TimePickerAndroid. Please report this in the bs-react-native repository",
    )
  };

[@bs.scope "TimePickerAndroid"] [@bs.module "react-native"]
external _open : optsJs => Js.Promise.t(responseJs) = "open";

let open_ = (~hour=?, ~minute=?, ~is24Hour=?, ~mode=`default, ()) =>
  _open(
    optsJs(
      ~hour=Js.Nullable.fromOption(hour),
      ~minute=Js.Nullable.fromOption(minute),
      ~is24Hour=Js.Nullable.fromOption(is24Hour),
      ~mode=modeToJs(mode),
    ),
  )
  |> Js.Promise.then_((resp: responseJs) =>
       resp |> actionHandler |> Js.Promise.resolve
     );
