using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Web.Mvc;
using SCPSInventory.DAL;
using SCPSInventory.Models;

namespace SCPSInventory.Controllers
{
    public class CostCentersController : Controller
    {
        private SCPSInventoryContext db = new SCPSInventoryContext();

        // GET: CostCenter
        public ActionResult List()
        {
            return View(db.CostCenters.ToList());
        }

        // GET: CostCenter/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: CostCenter/Create
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create([Bind(Include = "CostCenterId,Name")] CostCenter costCenter)
        {
            if (ModelState.IsValid)
            {
                db.CostCenters.Add(costCenter);
                db.SaveChanges();
                return RedirectToAction("List");
            }
            return View(costCenter);
        }
        public ActionResult validateUniqueCCID(string CostCenterId)
        {
            return Json(!db.CostCenters.Any(cc => cc.CostCenterId == CostCenterId), JsonRequestBehavior.AllowGet);
        }

        // GET: CostCenter/Edit/0021
        public ActionResult Edit(string id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            CostCenter costCenter = db.CostCenters.Find(id);
            if (costCenter == null)
            {
                return HttpNotFound();
            }
            return View(costCenter);
        }

        // POST: CostCenter/Edit/0021
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit([Bind(Include = "CostCenterId,Name")] CostCenter costCenter)
        {
            if (ModelState.IsValid)
            {
                db.Entry(costCenter).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("List");
            }
            return View(costCenter);
        }

        // GET: CostCenter/Delete/0021
        public ActionResult Delete(string id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            CostCenter costCenter = db.CostCenters.Find(id);
            if (costCenter == null)
            {
                return HttpNotFound();
            }
            costCenter.AssetList = db.Assets.Where(asset => asset.ccId == costCenter.CostCenterId).ToList();
            if (costCenter.AssetList.Count > 0)
            {
                return View("CannotDelete", costCenter);
            }
            return View(costCenter);
        }

        // POST: CostCenter/Delete/0021
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(string id)
        {
            CostCenter costCenter = db.CostCenters.Find(id);
            db.CostCenters.Remove(costCenter);
            db.SaveChanges();
            return RedirectToAction("List");
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }
    }
}
