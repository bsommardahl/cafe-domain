type t = {
  on: Date.t,
  by: string,
};

let toJs = (p: t) => {"on": p.on, "by": p.by};

let fromJs = p => {on: p##on, by: p##by};