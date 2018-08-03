[@bs.deriving jsConverter]
type t = {
  id: string,
  name: string,
};

module New = {
  [@bs.deriving jsConverter]
  type t = {name: string};
  let toJs = (expenseType: t) => {"name": expenseType.name};
};

type jsT = {
  .
  "_id": string,
  "name": string,
};

let fromJs = expenseTypeJs : t => {
  id: expenseTypeJs##_id,
  name: expenseTypeJs##name,
};

let toJsWithRev = (id: string, rev: option(string), expenseType: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "name": expenseType.name,
};

let toJs = (expenseType: t) : jsT => {
  "_id": expenseType.id,
  "name": expenseType.name,
};