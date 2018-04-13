type t = int;

let cleanNonNumeric = n => n |> Js.String.replaceByRe([%bs.re "/\\D/g"], "");

let toDisplay = t => (t |> string_of_int |> cleanNonNumeric) ++ "%";

let toFloat = t => float_of_int(t) /. 100.;

let calculate = (percent: t, num: int) =>
  int_of_float(float_of_int(num) *. (percent |> toFloat));

let toT = (str: string) : t =>
  switch (str |> cleanNonNumeric) {
  | "" => 0
  | s => s |> int_of_string
  };