type t = {
  id: string,
  name: string,
};

module New = {
  type t = {name: string};
  let toJs = (vendor: t) => {"name": vendor.name};
};

type jsT = {
  .
  "_id": string,
  "name": string,
};

let fromJs = vendorJs : t => {id: vendorJs##_id, name: vendorJs##name};

let toJsWithRev = (id: string, rev: option(string), vendor: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "name": vendor.name,
};

let toJs = (vendor: t) : jsT => {"_id": vendor.id, "name": vendor.name};