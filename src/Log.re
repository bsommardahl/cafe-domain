type t = {
  id: string,
  logType: string,
  level: int,
  message: string,
  payload: string,
  area: string,
  on: float,
};

module New = {
  type t = {
    logType: string,
    level: int,
    message: string,
    payload: string,
    area: string,
    on: float,
  };
  let toJs = (log: t) => {
    "logType": log.logType,
    "level": log.level,
    "message": log.message,
    "payload": log.payload,
    "area": log.area,
    "on": log.on,
  };
};

type jsT = {
  .
  "_id": string,
  "level": int,
  "logType": string,
  "message": string,
  "payload": string,
  "area": string,
  "on": float,
};

let fromJs = logJs : t => {
  id: logJs##_id,
  logType: logJs##logType,
  level: logJs##level,
  message: logJs##message,
  payload: logJs##payload,
  area: logJs##area,
  on: logJs##on,
};

let toJs = (log: t) : jsT => {
  "_id": log.id,
  "logType": log.logType,
  "level": log.level,
  "message": log.message,
  "payload": log.payload,
  "area": log.area,
  "on": log.on,
};