open Jest;

open Expect;

let unixTime = 1522292400000.;

let formatted = "28-3-2018 9:00 PM";

describe("Date functions", () => {
  describe("when converting from date float to sortable date", () =>
    describe("and float is a valid date", () =>
      test("it should return the corresponding date in YYYY-MM-DD format", () =>
        expect(unixTime |> Date.toISODate) |> toEqual("2018-03-28")
      )
    )
  );
  describe("when converting from sortable date to date float", () =>
    describe("and sortable date is valid", () =>
      test("it should return the corresponding date", () =>
        expect(unixTime |> Date.toISODate |> Date.fromISODate)
        |> toEqual(unixTime |> Date.startOfDay)
      )
    )
  );
  describe("when getting the start of the day", () =>
    test("it should return the corresponding date at midnight", () =>
      expect(unixTime |> Date.startOfDay |> Date.toDisplay)
      |> toEqual(1522216800000. |> Date.toDisplay)
    )
  );
  describe("when getting the end of the day", () =>
    test("it should return the corresponding date at 11:59:59", () =>
      expect(unixTime |> Date.endOfDay |> Date.toDisplay)
      |> toEqual(1522303199000. |> Date.toDisplay)
    )
  );
  describe("when converting", () => {
    describe("a float to a short time", () =>
      test("it should give only the time in short format", () =>
        expect(unixTime |> Date.toShortTime) |> toEqual("9:00 PM")
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
      |> toEqual("27-2-2018")
    );
  });
});