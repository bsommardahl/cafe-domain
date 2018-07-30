open Jest;

open Expect;

describe("util functions", () => {
  describe("when stripping of leading zeros", () => {
    describe("with non zero numbers", () => {
      let sample = "0031";
      test("it should remove only the leading zeros", () =>
        expect(sample |> Util.stripLeadingZeros) |> toEqual("31")
      );
    });
    describe("with only zeros", () => {
      let sample = "000";
      test("it should leave an empty string", () =>
        expect(sample |> Util.stripLeadingZeros) |> toEqual("")
      );
    });
  });
  describe("querystring parsing", () => {
    test("with keys and values", (_) => {
      let result = Util.QueryParam.get("theKey", "something=else&theKey=dog");
      expect(result) |> toEqual(Some("dog"));
    });
    test("an empty value should represent none", (_) => {
      let result = Util.QueryParam.get("theKey", "theKey=");
      expect(result) |> toEqual(None);
    });
    test("a nonexistent key represent none", (_) => {
      let result = Util.QueryParam.get("theKey", "");
      expect(result) |> toEqual(None);
    });
  });
});