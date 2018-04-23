type t = {
  id: string,
  logType: string,
  level: int,
  message: string,
  payload: string,
};

module New = {
  type t = {
    logType: string,
    level: int,
    message: string,
    payload: string,
  };
  let toJs = (log: t) => {
    "logType": log.logType,
    "level": log.level,
    "message": log.message,
    "payload": log.payload,
  };
};

type jsT = {
  .
  "_id": string,
  "level": int,
  "logType": string,
  "message": string,
  "payload": string,
};

let fromJs = logJs : t => {
  id: logJs##_id,
  logType: logJs##logType,
  level: logJs##level,
  message: logJs##message,
  payload: logJs##payload,
};

let toJs = (log: t) : jsT => {
  "_id": log.id,
  "logType": log.logType,
  "level": log.level,
  "message": log.message,
  "payload": log.payload,
};