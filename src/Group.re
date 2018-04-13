type group('a) = {
  key: string,
  value: list('a),
};

let by = (keyFn: 'a => string, list: list('a)) : list(group('a)) =>
  Belt.List.reduce(
    list,
    Js.Dict.empty(),
    (acc: Js.Dict.t(list('a)), cur: 'a) => {
      let key: string = keyFn(cur);
      let value = Js.Dict.get(acc, key);
      let items: list('a) =
        switch (value) {
        | None => []
        | Some(arr) => arr
        };
      Js.Dict.set(acc, key, List.concat([items, [cur]]));
      acc;
    },
  )
  |> Js.Dict.entries
  |> Array.to_list
  |> List.map(((k, v)) => {
       let g: group('a) = {key: k, value: v};
       g;
     });