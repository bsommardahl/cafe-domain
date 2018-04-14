type t = {
  id: string,
  name: string,
  url: string,
  event: string,
};

module New = {
  type t = {name: string};
  let toJs = (webhook: t) => {"name": webhook.name};
};

type jsT = {
  .
  "_id": string,
  "name": string,
};

let fromJs = webhookJs : t => {
  id: webhookJs##_id,
  name: webhookJs##name,
  url: webhookJs##url,
  event: webhookJs##event,
};

let toJsWithRev = (id: string, rev: option(string), webhook: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "name": webhook.name,
  "url": webhook.url,
  "event": webhook.event,
};

let toJs = (webhook: t) : jsT => {"_id": webhook.id, "name": webhook.name};