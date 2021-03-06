open! Helpers;

module Styles = PackageSummaryStyles;

let component = ReasonReact.statelessComponent("PackageSummary");

let make = (~package, _children) => {
  ...component,
  render: _self =>
    <div className=(Styles.root(package##_type))>
      <header className=Styles.header>
        <Link className=Styles.name href=("/packages/" ++ package##id)>
          (package##name |> text)
        </Link>
        <span className=Styles.version> (package##version |> text) </span>
        <span className=(Styles.unpublishedLabel(package##_type))>
          ("unpublished" |> text)
        </span>
        <div className=Styles.props>
          <span className=Styles.stars>
            (
              switch (package##stars |> Js.toOption) {
              | Some(stars) => stars |> text
              | None => "-" |> text
              }
            )
            <Icon.Star className=Styles.starIcon />
          </span>
          <Score package />
          (
            switch (package##license |> Js.toOption) {
            | Some(license) =>
              <span className=Styles.license> (license |> text) </span>
            | None =>
              <span className=Styles.nolicense> ("No license" |> text) </span>
            }
          )
          <span className=Styles.updated>
            <TimeAgo date=package##updated />
          </span>
        </div>
      </header>
      <div className=Styles.description>
        (
          switch package##description {
          | "" => nbsp
          | description => description |> text
          }
        )
      </div>
      <div className=Styles.tags>
        <Icon.Tags className=Styles.tagsIcon />
        <Control.Map items=package##keywords>
          ...(keyword => <Tag key=keyword name=keyword />)
        </Control.Map>
      </div>
    </div>
};