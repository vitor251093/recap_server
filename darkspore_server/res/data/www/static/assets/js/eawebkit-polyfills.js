// Polyfills should only be loaded for the EAWebKit
if (typeof Client !== 'undefined')
{
    // Array.isArray
    //   Reference:
    //   https://github.com/inexorabletash/polyfill/blob/master/es5.js
    Array.isArray = function (o) { return Boolean(o && Object.prototype.toString.call(Object(o)) === '[object Array]'); };
}
