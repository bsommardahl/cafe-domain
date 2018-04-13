open Jest;

open Expect;

let unixTime = 1522350507000.;

let formatted = "Thu Mar 29 2018 13:08:27 GMT-0600 (CST)";

describe("Date functions", () => {
  describe("when converting from date float to sortable date", () =>
    describe("and float is a valid date", () =>
      test("it should return the corresponding date in YYYY-MM-DD format", () =>
        expect(unixTime |> Date.toISODate) |> toEqual("2018-03-29")
      )
    )
  );
  describe("when getting the start of the day", () =>
    test("it should return the corresponding date at midnight", () =>
      expect(unixTime |> Date.startOfDay) |> toEqual(1522281600000.)
    )
  );
  describe("when getting the end of the day", () =>
    test("it should return the corresponding date at 11:59:59", () =>
      expect(unixTime |> Date.endOfDay) |> toEqual(1522367999000.)
    )
  );
  describe("when converting", () => {
    let unixTime = 1522350507000.;
    let formatted = "Thu Mar 29 2018 13:08:27 GMT-0600 (CST)";
    describe("a float to a short time", () =>
      test("it should give only the time in short format", () =>
        expect(1522433031521. |> Date.toShortTime) |> toEqual("12:03 PM")
      )
    );
    describe("a formatted date/time to a float", () =>
      test("it should parse the string to the correct float", () =>
        expect(formatted |> Date.toFloat) |> toEqual(unixTime)
      )
    );
    describe("a float to a formatted date/time", () =>
      test("it should format the float to a human readable format", () =>
        expect(unixTime |> Date.toDisplay) |> toEqual(formatted)
      )
    );
  });
  describe("when validating", () => {
    let valid = "Thu Mar 29 2018 13:08:27 GMT-0600 (CST)";
    let invalid = "Thu Mar 32 2018 13:08:27 GMT-0600 (CST)";
    describe("an invalid date/time to a float", () =>
      test("it should be false", () =>
        expect(invalid |> Date.isValid) |> toEqual(false)
      )
    );
    describe("a valid date/time to a float", () =>
      test("it should be true", () =>
        expect(valid |> Date.isValid) |> toEqual(true)
      )
    );
  });
  describe("when getting the date one month before", () => {
    let unixTime = 1522350507000.;
    test("it should give a date that is 30.44 days prior", () =>
      expect(unixTime |> Date.oneMonthBefore |> Date.toDisplayDate)
      |> toEqual("Tue Feb 27 2018")
    );
  });
});