// Generated by BUCKLESCRIPT VERSION 2.2.3, PLEASE EDIT WITH CARE
'use strict';


function toJs(webhook) {
  return {
          name: webhook[/* name */0],
          url: webhook[/* url */1],
          event: webhook[/* event */2]
        };
}

var New = /* module */[/* toJs */toJs];

function fromJs(webhookJs) {
  return /* record */[
          /* id */webhookJs._id,
          /* name */webhookJs.name,
          /* url */webhookJs.url,
          /* event */webhookJs.event
        ];
}

function toJsWithRev(id, rev, webhook) {
  return {
          _id: id,
          _rev: rev,
          name: webhook[/* name */1],
          url: webhook[/* url */2],
          event: webhook[/* event */3]
        };
}

function toJs$1(webhook) {
  return {
          _id: webhook[/* id */0],
          name: webhook[/* name */1],
          url: webhook[/* url */2],
          event: webhook[/* event */3]
        };
}

exports.New = New;
exports.fromJs = fromJs;
exports.toJsWithRev = toJsWithRev;
exports.toJs = toJs$1;
/* No side effect */