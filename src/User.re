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
  let toJs = (user: t) => {"name": user.name, "pin": user.pin};
};

type jsT = {
  .
  "_id": string,
  "name": string,
  "pin": string,
};

let fromJs = userJs: t => {
  id: userJs##_id,
  name: userJs##name,
  pin: userJs##pin,
};

let toJsWithRev = (id: string, rev: option(string), user: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "name": user.name,
  "pin": user.pin,
};

let toJs = (user: t): jsT => {
  "_id": user.id,
  "name": user.name,
  "pin": user.pin,
};