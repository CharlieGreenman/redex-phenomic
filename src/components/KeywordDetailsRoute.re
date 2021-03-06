open Helpers;

/* open Rebase; */
let component = ReasonReact.statelessComponent("Home");

type package = Typings.package;

let renderIdle = (packages: array(package)) =>
  <Control.Map items=packages>
    ...(package => <PackageSummary key=package##id package />)
  </Control.Map>;

let make =
    (~push, ~keyword, ~packages: PhenomicPresetReactApp.edge(array(package))) => {
  ...component,
  render: _self =>
    <IndexLayout push>
      <Helmet title=(Config.titleTemplate(keyword ++ " (keyword)")) />
      <h1> (keyword |> text) </h1>
      <DataLoading data=packages renderIdle />
    </IndexLayout>
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~packages=
        PhenomicPresetReactApp.jsEdgeToReason(jsProps##packageKeyword, a =>
          a##list
        ),
      ~push=jsProps##router##push,
      ~keyword=jsProps##params##keywords
    )
  );

let queries = props => {
  let packageKeyword =
    PhenomicPresetReactApp.query(
      List({
        path: "packages",
        by: Some("keywords"),
        value: Some(props##params##keywords),
        order: Some("asc"),
        limit: None
      })
    );
  /* TODO: Implement limit + pagination
     limit: Some(10)
     after: Some(string)
     */
  {"packageKeyword": packageKeyword};
};