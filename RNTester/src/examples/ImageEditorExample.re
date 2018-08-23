open Rebolt;
open Utils;
open Rebolt.ImageEditor;

let exampleType = Multiple;

let displayName = "ImageEditor";

let title = "<ImageEditor>";

let description = "Simple React Native ImageEditor component.";

let offset = {x: 25, y: 5};
let size = {width: 10, height: 10};
let displaySize = {width: 10, height: 10};
let resizeMode = `Cover;

type state = option(string);
type action =
  | SetPath(string);

let handleCropImage = (send, handler) =>
  ImageEditor.cropImage(
    ~uri=`URI("https://bit.ly/2ya4e2o"),
    ~offset,
    ~size,
    ~displaySize,
    ~resizeMode,
    ~success=successURI => send(handler(successURI)),
    ~failure=error => Js.log(error),
    (),
  );

module ImageEditorExample = {
  let component = ReasonReact.reducerComponent("ImageEditorExample");
  let make = _children => {
    ...component,
    initialState: () => None,
    reducer: (action, _state) =>
      switch (action) {
      | SetPath(path) => ReasonReact.Update(Some(path))
      },
    render: ({state, send}) =>
      <View>
        <Button
          onPress=(() => handleCropImage(send, link => SetPath(link)))
          title="Crop Image!"
          accessibilityLabel="Crop Image!"
        />
        (
          switch (state) {
          | None => <View />
          | Some(path) =>
            <Image
              source=(
                `URI(
                  Image.(
                    imageURISource(
                      ~uri=path,
                      ~width=Pt(320.),
                      ~height=Pt(480.),
                      (),
                    )
                  ),
                )
              )
            />
          }
        )
      </View>,
  };
};

let examples: array(Example.t) = [|
  {
    title: "ImageEditor example",
    description: None,
    render: () => <ImageEditorExample />,
  },
|];