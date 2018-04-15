type t = {
  id: string,
  name: string,
  pin: string,
};

module New = {
  type t = {
    name: string,
    pin: string,
  };
  let toJs = (cashier: t) => {"name": cashier.name, "pin": cashier.pin};
};

type jsT = {
  .
  "_id": string,
  "name": string,
  "pin": string,
};

let fromJs = cashierJs : t => {
  id: cashierJs##_id,
  name: cashierJs##name,
  pin: cashierJs##pin,
};

let toJsWithRev = (id: string, rev: option(string), cashier: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "name": cashier.name,
  "pin": cashier.pin,
};

let toJs = (cashier: t) : jsT => {
  "_id": cashier.id,
  "name": cashier.name,
  "pin": cashier.pin,
};