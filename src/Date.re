type t = float;

let now = Js.Date.now;

let day = 86400000.0;

let toDisplayDate = t =>
  Js.Date.fromFloat(t)
  |> (
    d => {
      let month = (d |> Js.Date.getMonth) +. 1.;
      let day = d |> Js.Date.getDate;
      let year = d |> Js.Date.getFullYear;
      (day |> int_of_float |> string_of_int)
      ++ "-"
      ++ (month |> int_of_float |> string_of_int)
      ++ "-"
      ++ (year |> int_of_float |> string_of_int);
    }
  );

let toStringWith2Digits = s =>
  if (s === 0) {
    "00";
  } else if (s < 10) {
    "0" ++ string_of_int(s);
  } else {
    string_of_int(s);
  };
let toISODate = t =>
  Js.Date.fromFloat(t)
  |> (
    d => {
      let month = (d |> Js.Date.getMonth) +. 1.;
      let day = d |> Js.Date.getDate;
      let year = d |> Js.Date.getFullYear;
      ""
      ++ (year |> int_of_float |> string_of_int)
      ++ "-"
      ++ (month |> int_of_float |> toStringWith2Digits)
      ++ "-"
      ++ (day |> int_of_float |> toStringWith2Digits);
    }
  );

let fromISODate = iso : t => {
  let p = iso |> Js.String.split("-");
  let d = p[1] ++ "/" ++ p[2] ++ "/" ++ p[0];
  let parsed = d |> Js.Date.parse;
  parsed |> Js.Date.getTime;
};

let fromISODateAndTime = (time, iso) => {
  let t = time |> Js.String.split(":");
  let newDate =
    iso
    |> fromISODate
    |> Js.Date.fromFloat
    |. Js.Date.setHoursMSMs(
         ~hours=t[0] |> float_of_string,
         ~minutes=t[1] |> float_of_string,
         ~seconds=0.,
         ~milliseconds=0.,
         (),
       );
  newDate;
};

let toDisplayTime = t =>
  Js.Date.fromFloat(t)
  |> (
    d => {
      let armyHours = d |> Js.Date.getHours |> int_of_float;
      let isPm = armyHours > 12;
      let hoursPossibleZero = isPm ? armyHours - 12 : armyHours;
      let hours = hoursPossibleZero == 0 ? 12 : hoursPossibleZero;
      let minutes = d |> Js.Date.getMinutes |> int_of_float;
      let ampm = isPm ? "PM" : "AM";
      string_of_int(hours)
      ++ ":"
      ++ (minutes |> toStringWith2Digits)
      ++ " "
      ++ ampm;
    }
  );

let toShortTime = toDisplayTime;

let toDisplay = t => (t |> toDisplayDate) ++ " " ++ (t |> toDisplayTime);

let fromDisplay = f => {
  let p = f |> Js.String.split(" ");
  let d_es = p[0];
  let d_es_p = d_es |> Js.String.split("-");
  let month = (d_es_p[1] |> float_of_string) -. 1.;
  let day = d_es_p[0] |> float_of_string;
  let year = d_es_p[2] |> float_of_string;
  let t_p = p[1] |> Js.String.split(":");
  let ampm = p[2];
  let hours = (t_p[0] |> float_of_string) +. (ampm === "PM" ? 12. : 0.);
  let minutes = t_p[1] |> float_of_string;
  let newDate =
    Js.Date.make()
    |. Js.Date.setFullYearMD(~year, ~month, ~date=day, ())
    |> Js.Date.fromFloat
    |. Js.Date.setHoursMSMs(
         ~hours,
         ~minutes,
         ~seconds=0.,
         ~milliseconds=0.,
         (),
       );
  newDate;
};

let oneMonthBefore = t => t -. day *. 30.44;

let addDays = (d: int, t) : t => t +. day *. float_of_int(d);

let addYears = (y: int, t) : t => {
  let jsDate = t |> Js.Date.fromFloat;
  let year = (jsDate |> Js.Date.getFullYear) +. (y |> float_of_int);
  let d = Js.Date.setFullYear(jsDate, year);
  d |> Js.Date.fromFloat |> Js.Date.getTime;
};

let startOfDay = (d: t) : t => {
  let jsDate = d |> Js.Date.fromFloat;
  let _ = Js.Date.setHoursMS(jsDate, ~hours=0., ~minutes=0., ~seconds=0., ());
  jsDate |> Js.Date.getTime;
};

let endOfDay = (d: t) : t => {
  let jsDate = d |> Js.Date.fromFloat;
  let _ =
    Js.Date.setHoursMS(jsDate, ~hours=23., ~minutes=59., ~seconds=59., ());
  jsDate |> Js.Date.getTime;
};

let isValid = (formattedDate: string) : bool => {
  let valid = formattedDate |> Js.Date.parse;
  switch (valid |> Js.Date.toString) {
  | "Invalid Date" => false
  | _ => true
  };
};

let fromString = str => str |> float_of_string;

let toDisplayFromOption = d =>
  switch (d) {
  | None => ""
  | Some(d) => d |> toDisplay
  };

let to24HourTime = t =>
  Js.Date.fromFloat(t)
  |> (
    d => {
      let hours = d |> Js.Date.getHours |> int_of_float;
      let minutes = d |> Js.Date.getMinutes |> int_of_float;
      string_of_int(hours) ++ ":" ++ (minutes |> toStringWith2Digits);
    }
  );

let toTimestamp = (t: float) =>
  (t |> toISODate) ++ "T" ++ (t |> to24HourTime);

let fromTimestamp = (ts: string) => {
  let d = ts |> Js.String.split("T");
  d[0] |> fromISODateAndTime(d[1]);
};