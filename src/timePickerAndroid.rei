type response = {
  hour: int,
  minute: int,
};

type action =
  | Dismissed
  | Set(response);

type mode =
  | Clock
  | Spinner
  | Default;

let open_:
  (~hour: int=?, ~minute: int=?, ~is24Hour: bool=?, ~mode: mode=?, unit) =>
  Js.Promise.t(action);
